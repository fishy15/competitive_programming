let solve () =
    let n = read_int () in
    let s = read_line () in
    let rec aux pos step =
        if pos < n then
            String.get s pos :: aux (pos + step) (step + 1)
        else
            []
    in
    List.iter (Printf.printf "%c") (aux 0 1);
    print_endline ""

let () = solve ()
