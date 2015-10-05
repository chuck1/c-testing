clear all;close all;clc

fid = fopen('u.bin');
u=fread(fid,[100 20],'double');
fclose(fid);

fid = fopen('v.bin');
v=fread(fid,[100 20],'double');
fclose(fid);

quiver(u,v)