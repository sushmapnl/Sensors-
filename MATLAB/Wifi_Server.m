t = tcpip('141.219.121.105', 80)
fopen(t)

fprintf(t, "%s", 'high' )

fscanf(t, "%s");

fclose(t)