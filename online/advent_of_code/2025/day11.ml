let rec read_input () =
    try
        let s = read_line () in
        s :: read_input ()
    with End_of_file -> []

let parse_input lines =
    let parse_line line =
        let tokens = String.split_on_char ' ' line in
        let first = List.hd tokens in
        let rest = List.drop 1 tokens in
        let node = String.sub first 0 (String.length first - 1) in
        (node, rest)
    in
    let adj = List.map parse_line lines in
    let graph = Hashtbl.create (List.length adj) in
    List.iter (fun (a, b) -> Hashtbl.replace graph a b) adj;
    graph

let toposort graph =
    let remaining_in = Hashtbl.create (Hashtbl.length graph) in
    let upd_incoming v nxt =
        let upd v =
            let old = Option.value ~default:0 (Hashtbl.find_opt remaining_in v) in
            Hashtbl.replace remaining_in v (old + 1)
        in
        List.iter upd nxt
    in
    Hashtbl.iter upd_incoming graph;
    let q = Queue.create () in
    let is_source v =
        let cnt = Option.value ~default:0 (Hashtbl.find_opt remaining_in v) in
        cnt = 0
    in
    Hashtbl.iter (fun v _ -> if is_source v then Queue.push v q else ()) graph;
    let rec aux () =
        match Queue.take_opt q with
        | None -> []
        | Some v ->
                (match Hashtbl.find_opt graph v with
                | None -> ()
                | Some nxt ->
                        let upd v =
                            let old_in = Hashtbl.find remaining_in v in
                            Hashtbl.replace remaining_in v (old_in - 1);
                            if old_in - 1 = 0 then
                                Queue.push v q
                            else ()
                        in
                        List.iter upd nxt);
                v :: aux ()
    in
    aux ()

let solve1 graph =
    let ord = toposort graph in
    let counts = Hashtbl.create (Hashtbl.length graph) in
    let upd v =
        let paths =
            if v = "you" then
                1
            else
                Option.value ~default:0 (Hashtbl.find_opt counts v)
        in
        let upd_nxt v =
            let old = Option.value ~default:0 (Hashtbl.find_opt counts v) in
            Hashtbl.replace counts v (old + paths)
        in
        match Hashtbl.find_opt graph v with
        | Some nxt -> List.iter upd_nxt nxt
        | None -> ()
    in
    List.iter upd ord;
    Hashtbl.find counts "out"

let add = Array.map2 (+)

let solve2 graph =
    let ord = toposort graph in
    let counts = Hashtbl.create (Hashtbl.length graph) in
    let default = [| 0; 0; 0; 0 |] in
    let upd v =
        let paths =
            if v = "svr" then
                [| 1; 0; 0; 0 |]
            else
                Option.value ~default:default (Hashtbl.find_opt counts v)
        in
        let upd_nxt v =
            let old = Option.value ~default:default (Hashtbl.find_opt counts v) in
            let to_add = match v with
            | "dac" -> [| 0; paths.(0) + paths.(1); 0; paths.(2) + paths.(3) |]
            | "fft" -> [| 0; 0; paths.(0) + paths.(2); paths.(1) + paths.(3) |]
            | _     -> paths
            in
            Hashtbl.replace counts v (add old to_add)
        in
        match Hashtbl.find_opt graph v with
        | Some nxt -> List.iter upd_nxt nxt
        | None -> ()
    in
    List.iter upd ord;
    let ans = Hashtbl.find counts "out" in
    ans.(3)

let () =
    let lines = read_input () in
    let graph = parse_input lines in
    Printf.printf "%d\n" (solve1 graph);
    Printf.printf "%d\n" (solve2 graph)
