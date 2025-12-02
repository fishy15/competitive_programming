let rec read_input () =
    try
        let s = read_line () in
        s :: read_input ()
    with End_of_file -> []

let rec crosses_zero pos steps dir = 
    match steps with
    | 0 -> false
    | _ -> let nxt = (pos + dir + 100) mod 100 in
           if nxt == 0 then 
               true
           else
               crosses_zero nxt (steps - 1) dir

let upd1 (cur_pos, cnt) s =
    let rot = int_of_string (String.(sub s 1 (length s - 1))) in
    let left = String.get s 0 = 'L' in
    let new_pos =
        if left then (cur_pos - rot + 100) mod 100
        else (cur_pos + rot) mod 100 in
    let cnt = if new_pos = 0 then cnt + 1 else cnt in
    (new_pos, cnt)

let upd2 (cur_pos, cnt) s =
    let rot = int_of_string (String.(sub s 1 (length s - 1))) in
    let cnt = cnt + (rot / 100) in
    let rot = rot mod 100 in
    let left = String.get s 0 = 'L' in
    let new_pos =
        if left then (cur_pos - rot + 100) mod 100
        else (cur_pos + rot) mod 100 in
    let cnt = if crosses_zero cur_pos rot (if left then -1 else 1) then cnt+1 else cnt in
    (new_pos, cnt)

let solve1 lines = List.fold_left upd1 (50, 0) lines |> Pair.snd
let solve2 lines = List.fold_left upd2 (50, 0) lines |> Pair.snd

let () =
    let lines = read_input () in
    Printf.printf "%d\n" (solve1 lines);
    Printf.printf "%d\n" (solve2 lines)
