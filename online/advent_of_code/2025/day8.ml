let rec read_input () =
    try
        let s = read_line () in
        s :: read_input ()
    with End_of_file -> []

type dsu = (int array * int array)

let dsu_init n =
    let dsu = Array.init n (Fun.id) in
    let size = Array.init n (fun _ -> 1) in
    dsu, size

let rec dsu_find (dsu, size) x =
    if dsu.(x) = x then
        x
    else
        let par = dsu.(x) in
        let ans = dsu_find (dsu, size) par in
        dsu.(x) <- ans;
        ans

let dsu_join (dsu, size) x y =
    let x = dsu_find (dsu, size) x in
    let y = dsu_find (dsu, size) y in
    if x <> y then
        let x, y = if x < y then y, x else x, y in
        let _ = (size.(x) <- size.(x) + size.(y)) in
        let _ = (dsu.(y) <- x) in
        true
    else
        false

let dsu_compsizes dsu =
    let n = Array.length (fst dsu) in
    let get_size x =
        if x = dsu_find dsu x then
            Some (snd dsu).(x)
        else
            None
    in
    List.filter_map get_size (List.init n Fun.id)

let parse_input lines =
    let parse_row row =
        let idx1 = String.index row ',' in
        let idx2 = String.index_from row (idx1 + 1) ',' in
        let len = String.length row in
        let num1 = int_of_string (String.sub row 0 idx1) in
        let num2 = int_of_string (String.sub row (idx1 + 1) (idx2 - idx1 - 1)) in
        let num3 = int_of_string (String.sub row (idx2 + 1) (len - idx2 - 1)) in
        (num1, num2, num3)
    in
    List.map parse_row lines 

let rec prod xs =
    match xs with
    | [] -> []
    | x :: rest -> (List.map (fun x2 -> (x, x2)) rest) @ prod rest

let abs x = if x < 0 then -x else x

let dist (x1, y1, z1) (x2, y2, z2) =
    let xdiff = abs (x1 - x2) in
    let ydiff = abs (y1 - y2) in
    let zdiff = abs (z1 - z2) in
    xdiff * xdiff + ydiff * ydiff + zdiff * zdiff

let compress pts =
    let n = List.length pts in
    let table = Hashtbl.create n in
    let rec aux pts added =
        match pts with
        | [] -> ()
        | p :: rest ->
                match Hashtbl.find_opt table p with
                | Some _ -> aux rest added
                | None ->
                        let _ = Hashtbl.replace table p added in
                        aux rest (added + 1)
    in
    aux pts 0;
    table

let solve1 points =
    let n = List.length points in
    let ht = compress points in
    let pairs = List.filter (fun (x, y) -> x <> y) @@ prod points in
    let pairs = List.fast_sort (fun (a, b) (c, d) -> Int.compare (dist a b) (dist c d)) pairs in
    let dsu = dsu_init n in
    let rec aux pairs left = match pairs, left with
    | [], _ -> ()
    | _, 0 -> ()
    | (a, b) :: rest, left ->
            let a = Hashtbl.find ht a in
            let b = Hashtbl.find ht b in
            let _ = dsu_join dsu a b in
                aux rest (left - 1)
    in
    aux pairs 1000;
    let compsizes = List.fast_sort (fun x y -> -Int.compare x y) @@ dsu_compsizes dsu in
    let a = List.nth compsizes 0 in
    let b = List.nth compsizes 1 in
    let c = List.nth compsizes 2 in
    a * b * c

let solve2 points =
    let n = List.length points in
    let ht = compress points in
    let pairs = List.filter (fun (x, y) -> x <> y) @@ prod points in
    let pairs = List.fast_sort (fun (a, b) (c, d) -> Int.compare (dist a b) (dist c d)) pairs in
    let dsu = dsu_init n in
    let rec aux pairs left ans = match pairs, left with
    | [], _ -> ans
    | _, 0 -> ans
    | (a, b) :: rest, left ->
            let (x1, _, _) = a in
            let (x2, _, _) = b in
            let a = Hashtbl.find ht a in
            let b = Hashtbl.find ht b in
            if dsu_join dsu a b then
                aux rest (left - 1) (x1 * x2)
            else
                aux rest left ans
    in
    aux pairs 1000 0

let () =
    let lines = read_input () in
    let points = parse_input lines in
    Printf.printf "%d\n" (solve1 points);
    Printf.printf "%d\n" (solve2 points)
