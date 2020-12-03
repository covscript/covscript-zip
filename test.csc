import zip
var z = zip.open("./a.zip", zip.openmode.append)
if !z.is_open()
    system.out.println("Error on open!")
    system.exit(0)
end
var e = z.get_entries()
if e != null
    system.out.println("Error on get_entries!")
end