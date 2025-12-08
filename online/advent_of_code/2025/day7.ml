let rec read_input () =
    try
        let s = read_line () in
        s :: read_input ()
    with End_of_file -> []

let remove_dups xs =
    let xs = List.fast_sort Int.compare xs in
    let rec aux xs =
        match xs with
        | [] -> []
        | [x] -> [x]
        | x :: y :: xs ->
                if x = y then
                    aux (y :: xs)
                else
                    x :: aux (y :: xs)
    in
    aux xs

let compress_dups xs =
    let xs = List.fast_sort (fun (a, _) (b, _) -> Int.compare a b) xs in
    let rec aux xs acc =
        match xs with
        | [] -> []
        | [(x, c)] -> [(x, acc + c)]
        | (x, c) :: y :: xs ->
                if x = fst y then
                    aux (y :: xs) (acc + c)
                else
                    (x, acc + c) :: aux (y :: xs) 0
    in
    aux xs 0

let solve1 grid =
    let start_row = List.hd grid in
    let remaining_rows = List.drop 1 grid in
    let starts = List.singleton (String.index start_row 'S') in
    let width = String.length start_row in
    let process_row (splits, beams) row =
        let update_beam idx =
            let splits, beams = 
                if String.get row idx = '^' then
                    1, [ idx - 1; idx + 1 ]
                else
                    0, [ idx ]
            in
            splits, List.filter (fun i -> 0 <= i && i < width) beams
        in
        let beam_results = List.map update_beam beams in
        let splits = splits + (List.fold_left (fun acc (s, _) -> s + acc) 0 beam_results) in
        let beams = remove_dups (List.concat_map (fun (_, xs) -> xs) beam_results) in
        splits, beams
    in
    let ans, _ = List.fold_left process_row (0, starts) remaining_rows in
    ans

let solve2 grid =
    let start_row = List.hd grid in
    let remaining_rows = List.drop 1 grid in
    let starts = List.singleton ((String.index start_row 'S'), 1) in
    let width = String.length start_row in
    let process_row beams row =
        let update_beam (idx, cnt) =
            let beams = 
                if String.get row idx = '^' then
                    [ (idx - 1, cnt); (idx + 1, cnt) ]
                else
                    [ (idx, cnt) ]
            in
            List.filter (fun (i, _) -> 0 <= i && i < width) beams
        in
        let beam_results = List.concat_map update_beam beams in
        compress_dups beam_results
    in
    let final_beams = List.fold_left process_row starts remaining_rows in
    List.fold_left (fun acc (_, c) -> acc + c) 0 final_beams

let () =
    let grid = read_input () in
    Printf.printf "%d\n" (solve1 grid);
    Printf.printf "%d\n" (solve2 grid)
