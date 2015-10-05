clear all;close all;clc

fid = fopen('u.bin');
u=fread(fid,[10 10],'double');
fclose(fid);

fid = fopen('u.bin');
v=fread(fid,[10 10],'double');
fclose(fid);

quiver(u,v)