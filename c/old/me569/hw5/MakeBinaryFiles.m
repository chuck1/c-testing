
load u1
fid = fopen('u1.bin', 'w');
fwrite(fid, u1)
fclose(fid);

load u2
fid = fopen('u2.bin', 'w');
fwrite(fid, u2)
fclose(fid);

load u3
fid = fopen('u3.bin', 'w');
fwrite(fid, u3)
fclose(fid);

load v1
fid = fopen('v1.bin', 'w');
fwrite(fid, v1)
fclose(fid);

load v2
fid = fopen('v2.bin', 'w');
fwrite(fid, v2)
fclose(fid);

load v3
fid = fopen('v3.bin', 'w');
fwrite(fid, v3)
fclose(fid);

load w1
fid = fopen('w1.bin', 'w');
fwrite(fid, w1)
fclose(fid);

load w2
fid = fopen('w2.bin', 'w');
fwrite(fid, w2)
fclose(fid);

load w3
fid = fopen('w3.bin', 'w');
fwrite(fid, w3)
fclose(fid);

load y.dat
fid = fopen('y.bin', 'w');
fwrite(fid, y)
fclose(fid);
