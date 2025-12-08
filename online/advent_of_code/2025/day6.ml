let rec read_input () =
    try
        let s = read_line () in
        s :: read_input ()
    with End_of_file -> []

type op =
| Add
| Mul

let op_of_str op =
    if op = "+" then Add else Mul

let split_noempty str =
    let str = String.split_on_char ' ' str in
    List.filter (fun x -> String.length x > 0) str

let rec zip (xs : 'a list) (ys : 'b list) : ('a * 'b) list =
    match xs, ys with
    | [], _ -> []
    | _, [] -> []
    | x :: xs, y :: ys -> (x, y) :: zip xs ys

let rec transpose (xss : 'a list list) : 'a list list =
    match xss with
    | [] -> []
    | xs :: [] -> List.map (fun x -> [x]) xs
    | xs :: xss -> List.map2 (fun x xs -> x :: xs) xs (transpose xss)

let parse_input lines =
    let n = List.length lines in
    let rows = List.take (n - 1) lines in
    let process_row row =
        let row = split_noempty row in
        List.map int_of_string row
    in
    let rows = List.map process_row rows in
    let last = List.nth lines (n - 1) |> split_noempty |> List.map op_of_str in
    (rows, last)

let process_group (xs : string list) : int list =
    let xs = List.map (fun x -> List.of_seq (String.to_seq x)) xs in
    let xs = transpose xs in
    let xs = List.map (fun x -> List.filter (fun c -> c <> ' ') x) xs in
    let xs = List.map (fun x -> String.of_seq (List.to_seq x)) xs in
    let xs = List.filter (fun x -> String.length x > 0) xs in
    List.map int_of_string xs

let parse_input2 lines =
    let n = List.length lines in
    let rows = List.take (n - 1) lines in
    let last = List.nth lines (n - 1) in
    let m = String.length last in
    let dividers = List.init m Fun.id |> List.filter (fun idx -> String.get last idx <> ' ') in
    let rec get_groups (divs : int list) =
        let extract_range l r = List.map (fun s -> String.sub s l (r - l)) rows in
        match divs with
        | cur :: nxt :: rest -> extract_range cur nxt :: get_groups (nxt :: rest)
        | cur :: [] -> extract_range cur m :: []
        | [] -> []
    in
    let rows = List.map process_group (get_groups dividers) in
    let last = last |> split_noempty |> List.map op_of_str in
    (rows, last)

let eval op xs =
    match op with
    | Add -> List.fold_left (+) 0 xs
    | Mul -> List.fold_left ( * ) 1 xs

let solve1 rows ops =
    let cols = transpose rows in
    let vals = List.map2 eval ops cols in
    List.fold_left (+) 0 vals

let solve2 rows ops =
    let vals = List.map2 eval ops rows in
    List.fold_left (+) 0 vals

let () =
    let inp = read_input () in
    let rows, ops = parse_input inp in
    Printf.printf "%d\n" (solve1 rows ops);
    let rows, ops = parse_input2 inp in
    Printf.printf "%d\n" (solve2 rows ops)
