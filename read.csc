import zip
var z = zip.open("./a.zip", zip.openmode.read)
var e = z.get_entries()
foreach it in e do system.out.println(it.name)