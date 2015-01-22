import libstatfs
sd = libstatfs.stat_dir()
sd.read()
l = sd.get_dirs()
print l
