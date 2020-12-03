import zip
var z = zip.open("./a.zip", zip.openmode.write)
if !z.is_open()
    system.out.println("Error!")
    system.exit(0)
end
z.entry_add("write.csc", "./write.csc")
z.entry_add("zip.cpp", "./zip.cpp")
z = null
z = zip.open("./a.zip", zip.openmode.append)
z.entry_add("read.csc", "./read.csc")
z.entry_delete("zip.cpp")
#var e = z.get_entries()
#if e != null
#    system.out.println("Error!")
#end