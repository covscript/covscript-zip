import zip
var z = zip.open("./a.zip", zip.openmode.read)
loop
    system.out.println("Zip Entries:")
    var e = z.get_entries()
    foreach i in range(e.size)
        system.out.println(to_string(i + 1) + "\t" + e[i].name)
    end
    var idx = null
    system.out.println("")
    loop
        system.out.print("Please select:")
        idx = system.in.input()
        if typeid idx == typeid number && idx > 0 && idx <= e.size
            break
        else
            system.out.print("Format Error!")
        end
    end
    var buff = new iostream.char_buff
    z.read_entry_stream(e[idx - 1].name, buff.get_ostream())
    system.out.println(buff.get_string())
    system.out.println("")
end