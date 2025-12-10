let rec read_input () =
    try
        let s = read_line () in
        s :: read_input ()
    with End_of_file -> []

let parse_input lines =
    let parse_row row =
        let idx = String.index row ',' in
        let len = String.length row in
        let num1 = int_of_string (String.sub row 0 idx) in
        let num2 = int_of_string (String.sub row (idx + 1) (len - idx - 1)) in
        (num1, num2)
    in
    List.map parse_row lines 

let rec prod xs =
    match xs with
    | [] -> []
    | x :: rest -> (List.map (fun x2 -> (x, x2)) rest) @ prod rest

let rec prod2 xs ys =
    List.concat_map (fun x -> List.map (fun y -> (x, y)) ys) xs

let area (a, b) (c, d) = (abs (a - c) + 1) * (abs (b - d) + 1)

let rec toggle_order xs x = 
    match xs with
    | [] -> [x]
    | hd :: tl -> 
            if x = hd then
                tl
            else if x < hd then
                x :: hd :: tl
            else 
                hd :: toggle_order tl x

let point_compare (x1, y1) (x2, y2) =
    if x1 = x2 then Int.compare y1 y2
    else Int.compare x1 x2

let merge xs ys =
    let pts = List.fast_sort point_compare (xs @ ys) in
    let rec aux ps = match ps with
    | [] -> []
    | [p] -> [p]
    | p1 :: p2 :: rest ->
            if p1 = p2 then
                p1 :: aux rest
            else
                p1 :: aux (p2 :: rest)
    in
    aux pts

let compress_ht pts =
    let n = List.length pts in
    let table = Hashtbl.create n in
    let pts = List.fast_sort Int.compare pts in
    let rec aux pts added =
        match pts with
        | [] -> ()
        | p :: rest ->
                match Hashtbl.find_opt table p with
                | Some _ -> aux rest added
                | None ->
                        let _ = Hashtbl.replace table p added in
                        aux rest (added + 2)
    in
    aux pts 0;
    table

let compress_points points =
    let ht_x = compress_ht (List.map fst points) in
    let ht_y = compress_ht (List.map snd points) in
    let points = List.map (fun (x, y) -> (Hashtbl.find ht_x x), (Hashtbl.find ht_y y)) points in
    ht_x, ht_y, points

let construct points =
    let ht_x, ht_y, points = compress_points points in
    let points = List.fast_sort point_compare points in
    let max_x = List.fold_left (fun acc (x, _) -> max acc x) 0 points in
    let rec aux cur_x pts ord orig acc =
        match cur_x, pts, orig with
        | _, _, _ when cur_x = max_x + 1 -> acc
        | _, _, None -> aux cur_x pts ord (Some ord) acc
        | _, (x, y) :: tl, _ when x = cur_x -> aux cur_x tl (toggle_order ord y) orig acc
        | _, _, Some orig ->
                let rec aux2 = function
                    | [] -> []
                    | [y] -> []
                    | y1 :: y2 :: rest ->
                            List.init (y2 - y1 + 1) (fun y -> (cur_x, y1 + y)) @ aux2 rest
                in
                let pts1 = aux2 ord in
                let pts2 = aux2 orig in
                let acc = merge pts1 pts2 @ acc in
                aux (cur_x + 1) pts ord None acc
    in
    let res = aux 0 points [] None [] in
    ht_x, ht_y, res

let solve1 points =
    let pairs = prod points in
    let areas = List.map (fun (x, y) -> area x y) pairs in
    List.fold_left max 0 areas

let minmax a b =
    if a < b then
        a, b
    else
        b, a

let add_to_map pts =
    let ht = Hashtbl.create (List.length pts) in
    let rec aux = function
        | [] -> ()
        | x :: rest -> Hashtbl.replace ht x (); aux rest
    in
    aux pts;
    ht

let solve2 points =
    let pairs = prod points in
    let ht_x, ht_y, filled = construct points in
    let filled = add_to_map filled in
    Random.init 10;
    let works (x1, y1) (x2, y2) =
        let x1, x2 = minmax x1 x2 in
        let y1, y2 = minmax y1 y2 in
        let x1 = Hashtbl.find ht_x x1 in
        let x2 = Hashtbl.find ht_x x2 in
        let y1 = Hashtbl.find ht_y y1 in
        let y2 = Hashtbl.find ht_y y2 in
        let rec aux left = match left with
        | 0 -> true
        | _ -> let x = Random.int_in_range ~min:x1 ~max:x2 in
               let y = Random.int_in_range ~min:y1 ~max:y2 in
               Hashtbl.mem filled (x, y) && aux (left - 1) 
        in
        aux 10000
    in
    let pairs = List.filter (fun (p1, p2) -> works p1 p2) pairs in
    let areas = List.map (fun (x, y) -> area x y) pairs in
    List.fold_left max 0 areas

let () =
    let lines = read_input () in
    let points = parse_input lines in
    Printf.printf "%d\n" (solve1 points);
    Printf.printf "%d\n" (solve2 points)
