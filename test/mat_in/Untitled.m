test = [1.234 -3.468];
fid = fopen('test.bin', 'w');
fwrite(fid, test, 'double')
fclose(fid);

load u1
fid = fopen('u1.bin', 'w');
fwrite(fid, u1)
fclose(fid);