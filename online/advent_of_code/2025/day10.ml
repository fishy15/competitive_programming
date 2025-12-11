let rec read_input () =
    try
        let s = read_line () in
        s :: read_input ()
    with End_of_file -> []

let parse_input lines =
    let parse_indicator repr =
        let n = String.length repr in
        let repr = String.sub repr 1 (n - 2) in
        let n = String.length repr in
        let rec aux idx =
            if idx = n then 0
            else
                let cur = String.get repr idx in
                let cur = if cur = '#' then 1 else 0 in
                2 * (aux (idx + 1)) + cur
        in
        aux 0
    in
    let parse_button repr = 
        let orig_len = String.length repr in
        let repr = String.sub repr 1 (orig_len - 2) in
        List.map int_of_string @@ String.split_on_char ',' repr
    in
    let parse_joltage repr =
        let orig_len = String.length repr in
        let repr = String.sub repr 1 (orig_len - 2) in
        List.map int_of_string @@ String.split_on_char ',' repr
    in
    let parse_row row =
        let groups = String.split_on_char ' ' row in
        let len = List.length groups in
        let indicator = List.hd groups in
        let buttons = List.(drop 1 @@ take (len - 1) groups) in
        let joltage = List.nth groups (len - 1) in
        (String.length indicator - 2, parse_indicator indicator, List.map parse_button buttons, parse_joltage joltage)
    in
    List.map parse_row lines 

let next_pow2 x =
    let rec aux cur =
        if x < cur then
            cur
        else
            aux (2 * cur)
    in
    aux 1

let apply_button v buttons =
    let flip acc x = acc lxor (1 lsl x) in
    List.fold_left flip v buttons

let min_buttons (spaces, indicator, buttons, _) =
    let n_states = 1 lsl spaces in
    let dp = Array.make n_states None in
    let q = Queue.create () in
    Queue.push (0, 0) q;
    dp.(0) <- Some 0;
    let rec aux () =
        match Queue.take_opt q with
        | None -> ()
        | Some (v, cur_d) ->
                let try_button b =
                    let v = apply_button v b in
                    match dp.(v) with
                    | Some _ -> ()
                    | None ->
                        let _ = (dp.(v) <- Some (cur_d + 1)) in
                        Queue.push (v, cur_d + 1) q
                in
                List.iter try_button buttons;
                aux ()
    in
    aux ();
    Option.get dp.(indicator)

let min_buttons2 (_, _, buttons, joltage) =
    let problem =
        let open Lp in
        let num_buttons = List.length buttons in
        let vars = Array.init num_buttons (fun i -> Lp.var ~integer:true (Printf.sprintf "c%d" i)) in
        let sum_vars = Array.fold_left (++) (c 0.) vars in
        let obj = minimize sum_vars in
        let nonneg = List.map (fun v -> v >~ (c 0.)) @@ List.of_seq @@ Array.to_seq vars in
        let eq_joltage idx =
            let var_if_idx bidx var =
                let button = List.nth buttons bidx in
                if List.mem idx button then
                    var
                else
                    c 0.
            in
            let total_presses = Array.fold_left (++) (c 0.) @@ Array.mapi var_if_idx vars in
            total_presses =~ (c (float_of_int (List.nth joltage idx)))
        in
        let joltage_constr = List.init (List.length joltage) eq_joltage in
        make obj @@ List.concat [nonneg; joltage_constr]
    in
    match Lp_glpk.solve ~term_output:false problem with
    | Ok (obj, _) -> int_of_float obj
    | Error _ -> exit 1

let solve1 cases =
    let ans = List.map min_buttons cases in
    List.fold_left (+) 0 ans

let solve2 cases =
    let ans = List.map min_buttons2 cases in
    List.fold_left (+) 0 ans

let () =
    let lines = read_input () in
    let cases = parse_input lines in
    Printf.printf "%d\n" (solve1 cases);
    Printf.printf "%d\n" (solve2 cases)
