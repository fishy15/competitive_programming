let rec read_input () =
    try
        let s = read_line () in
        s :: read_input ()
    with End_of_file -> []

let parse_range str =
    let n = String.length str in
    let idx = String.index_from str 0 '-' in
    let l = int_of_string (String.sub str 0 idx) in
    let r = int_of_string (String.sub str (idx + 1) (n - idx - 1)) in
    (l, r)

let parse_input (lines : string list) : (int * int) list * int list =
    let ranges = List.take_while (fun x -> String.length x > 0) lines in
    let queries = List.drop 1 (List.drop_while (fun x -> String.length x > 0) lines) in
    let ranges = List.map parse_range ranges in
    let queries = List.map int_of_string queries in
    (ranges, queries)

let in_range (l, r) x = l <= x && x <= r

let solve1 ranges queries =
    let check_good x = List.exists (fun r -> in_range r x) ranges in
    List.length (List.filter check_good queries)

let cmp (a, b) (c, d) =
    if a == c then Int.compare b d
    else Int.compare a c

let solve2 (ranges : (int * int) list) : int =
    let starts = List.map (fun (l, _) -> (l, +1)) ranges in
    let ends = List.map (fun (_, r) -> (r + 1, -1)) ranges in
    let events = List.concat [starts; ends] in
    let events = List.fast_sort cmp events in
    let rec aux events last_pos cur_val sum =
        match events with
        | [] -> sum
        | (x, delta) :: tail ->
                let sum = sum + (if cur_val > 0 then (x - last_pos) else 0)in
                let cur_val = cur_val + delta in
                aux tail x cur_val sum
    in
    aux events 0 0 0

let () =
    let inp = read_input () in
    let ranges, queries = parse_input inp in
    Printf.printf "%d\n" (solve1 ranges queries);
    Printf.printf "%d\n" (solve2 ranges)
