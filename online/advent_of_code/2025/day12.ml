let rec read_input () =
    try
        let s = read_line () in
        s :: read_input ()
    with End_of_file -> []

let parse_input lines =
    let parse_line line =
        let groups = String.split_on_char ' ' line in
        let dims = List.hd groups in
        let rest = List.map int_of_string (List.drop 1 groups) in
        let a = int_of_string (String.sub dims 0 2) in
        let b = int_of_string (String.sub dims 3 2) in
        (a, b, rest)
    in
    List.map parse_line lines

let used = [7; 5; 7; 6; 7; 7]

let all_fits (n, m, counts) =
    let squares = (n / 3) * (m / 3) in
    let total_3x3 = List.fold_left (+) 0 counts in
    let total_used = List.fold_left2 (fun acc a b -> acc + a * b) 0 counts used in
    if squares >= total_3x3 then
        true
    else if total_used > n * m then
        false
    else
        let _ = Printf.printf "BAD: %d %d %d %d [" n m squares total_3x3 in
        let _ = List.iter (Printf.printf "%d ") counts in
        let _ = print_endline "]" in
        false

let solve1 tests =
    List.length (List.filter all_fits tests)

let () =
    let lines = read_input () in
    let tests = parse_input lines in
    Printf.printf "%d\n" (solve1 tests)
