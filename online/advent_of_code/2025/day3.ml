let rec read_input () =
    try
        let s = read_line () in
        s :: read_input ()
    with End_of_file -> []

let largest_joltage2 batteries =
    let n = String.length batteries in
    let get_digit idx =
        let d = String.get batteries idx in
        Char.code d - Char.code '0'
    in
    let rec second idx =
        if idx = n then None
        else
            let digit2 = get_digit idx in
            let ans = match (second (idx + 1)) with
            | Some v -> max v digit2
            | None -> digit2
            in
            Some ans
    in
    let rec first idx =
        if idx = n then None
        else 
            let digit1 = get_digit idx in
            let next_best = Option.value ~default:0 (first (idx + 1)) in
            let ans = match (second (idx + 1)) with
            | Some digit2 -> max next_best (10 * digit1 + digit2)
            | None -> next_best
            in
            Some ans
    in
    Option.value ~default:0 (first 0)

type value =
| Undefined
| Value of int

let value_add x y = match x, y with
| Undefined, other -> Undefined
| other, Undefined -> Undefined
| (Value v1), (Value v2) -> Value (v1 + v2)

let value_max x y = match x, y with
| Undefined, other -> other
| other, Undefined -> other
| (Value v1), (Value v2) -> Value (max v1 v2)

let largest_joltage num batteries =
    let n = String.length batteries in
    let get_digit idx =
        let d = String.get batteries idx in
        Char.code d - Char.code '0'
    in
    let rec pow10 = function
    | 0 -> 1
    | n -> 10 * pow10 (n - 1)
    in
    let init = Array.init (num + 1) (fun i -> if i = 0 then (Value 0) else Undefined) in
    let rec recurse idx nxt_dp =
        let d = get_digit idx in
        let comp_idx cnt =
            if cnt = 0 then nxt_dp.(cnt)
            else 
                let v1 = nxt_dp.(cnt) in
                let v2 = value_add (nxt_dp.(cnt - 1)) (Value (d * pow10 (cnt - 1))) in
                value_max v1 v2
        in
        let dp = Array.init (num + 1) comp_idx in
        match idx with
        | 0 -> dp.(num)
        | _ -> recurse (idx - 1) dp
    in
    match recurse (n - 1) init with
    | Undefined -> 0
    | Value v -> v

let solve1 batteries = batteries |> List.map (largest_joltage 2) |> List.fold_left (+) 0
let solve2 batteries = batteries |> List.map (largest_joltage 12) |> List.fold_left (+) 0

let () =
    let batteries = read_input () in
    Printf.printf "%d\n" (solve1 batteries);
    Printf.printf "%d\n" (solve2 batteries)
