open Core
open Solutions

let () =
    let day = (Array.get (Sys.get_argv ()) 1) in
    let defaultfn () = "N/A" in
    let (part1fn, part2fn) = match day with
        | "1" -> (Day1.part1, Day1.part2)
        | "2" -> (Day2.part1, Day2.part2)
        | _ -> (defaultfn, defaultfn)
    in
    Printf.printf "[Day %s]\n\tPart 1 => %s\n\tPart 2 => %s\n"
        day
        (part1fn ())
        (part2fn ());
