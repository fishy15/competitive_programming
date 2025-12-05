let rec read_input () =
    try
        let s = read_line () in
        s :: read_input ()
    with End_of_file -> []

let adj = [
    (-1, -1);
    (-1, 0);
    (-1, 1);
    (0, -1);
    (0, 1);
    (1, -1);
    (1, 0);
    (1, 1)
]

let product (xs : 'a list) (ys : 'a list) : ('a * 'b) list =
    let zip_value x = List.map (fun y -> (x, y)) ys in
    List.concat (List.map zip_value xs)

let sum_some (xs : int option list) : int =
    let combine (acc : int) (x : int option) : int = 
        match x with
        | Some v -> acc + v
        | None -> acc
    in
    List.fold_left combine 0 xs

let count_ok (grid : char array array) : int =
    let n = Array.length grid in
    let m = Array.length grid.(0) in
    let row_idx = List.init n Fun.id in
    let col_idx = List.init m Fun.id in
    let idxs = product row_idx col_idx in
    let get_opt x y =
        if 0 <= x && x < n && 0 <= y && y < m then
            Some (if grid.(x).(y) = '@' then 1 else 0)
        else
            None
    in
    let is_ok (x, y) =
        let get_offset (dx, dy) = get_opt (x + dx) (y + dy) in
        let adj_values = List.map get_offset adj in
        grid.(x).(y) = '@' && sum_some adj_values < 4
    in
    List.length (List.filter is_ok idxs)

let count_ok_iter (grid : char array array) : int =
    let n = Array.length grid in
    let m = Array.length grid.(0) in
    let row_idx = List.init n Fun.id in
    let col_idx = List.init m Fun.id in
    let idxs = product row_idx col_idx in
    let get_opt x y =
        if 0 <= x && x < n && 0 <= y && y < m then
            Some (if grid.(x).(y) = '@' then 1 else 0)
        else
            None
    in
    let count_map = Hashtbl.create (n * m) in
    let visited = Hashtbl.create (n * m) in
    let queue = Queue.create () in
    let ans = ref 0 in
    let set_ok (x, y) =
        let get_offset (dx, dy) = get_opt (x + dx) (y + dy) in
        let adj_values = List.map get_offset adj in
        let adj_count = sum_some adj_values in
        Hashtbl.replace count_map (x, y) adj_count;
        if grid.(x).(y) = '@' && adj_count < 4 then
            let _ = Queue.add (x, y) queue in
            Hashtbl.replace visited (x, y) ()
    in
    List.iter set_ok idxs;
    let rec aux () =
        match Queue.peek_opt queue with
        | Some (x, y) ->
            ans := !ans + 1;
            Queue.drop queue;
            let sub_adj (dx, dy) =
                let x = x + dx in
                let y = y + dy in
                if 0 <= x && x < n && 0 <= y && y < m then
                    let adj_count = Hashtbl.find count_map (x, y) in
                    let adj_count = adj_count - 1 in 
                    let _ = Hashtbl.replace count_map (x, y) adj_count in
                    if grid.(x).(y) = '@' && adj_count < 4 && not (Hashtbl.mem visited (x, y)) then
                        let _ = Queue.push (x, y) queue in
                        Hashtbl.replace visited (x, y) ()
                    else ()
                else ()
            in
            List.iter sub_adj adj;
            aux ()
        | None -> ()
    in
    aux ();
    !ans

let solve1 grid = count_ok grid
let solve2 grid = count_ok_iter grid

let () =
    let grid = read_input () in
    let grid = Array.of_list (List.map (fun row -> Array.of_seq (String.to_seq row)) grid) in
    Printf.printf "%d\n" (solve1 grid);
    Printf.printf "%d\n" (solve2 grid)
