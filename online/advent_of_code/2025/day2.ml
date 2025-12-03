let is_invalid_2 n =
    let n = string_of_int n in
    let half = (String.length n) / 2 in
    let first = String.sub n 0 half in
    let second = String.sub n half (String.length n - half) in
    first = second

let is_invalid_any n =
    let n = string_of_int n in
    let len = String.length n in
    let rec get_substrs cur step =
        if cur >= len then []
        else String.sub n cur step :: get_substrs (cur + step) step
    in
    let try_len steps =
        if len mod steps <> 0 then false
        else
            let substrs = get_substrs 0 steps in
            let first = List.hd substrs in
            List.for_all (fun s -> s = first) substrs
    in
    let rec rec_try cur_step =
        if cur_step >= len then false
        else try_len cur_step || rec_try (cur_step + 1)
    in
    rec_try 1

let rec sum_invalid inv l r =
    if l > r then 0
    else
        let cur = if inv l then l else 0 in
        cur + sum_invalid inv (l + 1) r

let get_invalid inv range =
    let idx = String.index range '-' in
    let len = String.length range in
    let l = int_of_string @@ String.sub range 0 idx in
    let r = int_of_string @@ String.sub range (idx + 1) (len - idx - 1) in
    sum_invalid inv l r

let solve1 ranges = 
    let upd = fun acc range -> acc + get_invalid is_invalid_2 range in
    List.fold_left upd 0 ranges

let solve2 ranges = 
    let upd = fun acc range -> acc + get_invalid is_invalid_any range in
    List.fold_left upd 0 ranges


let () =
    let ranges = String.split_on_char ',' (read_line ()) in
    Printf.printf "%d\n" (solve1 ranges);
    Printf.printf "%d\n" (solve2 ranges)
