set encoding utf8
set terminal png size 1280, 720 enhanced font "Alegreya,18"
# set terminal pdfcairo enhanced color dashed font "Alegreya, 14" \
# set terminal epslatex color colortext
# rounded size 16 cm, 9.6 cm
set print "-"
set key on
set key bottom right
set auto
set grid
set size 1,1
set macro

# Standard border
set style line 11 lc rgb '#808080' lt 1 lw 3
set border 0 back ls 11
set tics out nomirror

# Standard grid
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12
# unset grid

set style line 1 lc rgb '#E41A1C' pt 1 ps 1 lt 1 lw 2 # red
set style line 2 lc rgb '#377EB8' pt 6 ps 1 lt 1 lw 2 # blue
set style line 3 lc rgb '#4DAF4A' pt 2 ps 1 lt 1 lw 2 # green
set style line 4 lc rgb '#984EA3' pt 3 ps 1 lt 1 lw 2 # purple
set style line 5 lc rgb '#FF7F00' pt 4 ps 1 lt 1 lw 2 # orange
set style line 6 lc rgb '#FFFF33' pt 5 ps 1 lt 1 lw 2 # yellow
set style line 7 lc rgb '#A65628' pt 7 ps 1 lt 1 lw 2 # brown
set style line 8 lc rgb '#F781BF' pt 8 ps 1 lt 1 lw 2 # pink

fileposfix = "10-1 10-5 10-8"
zvariance = "10 100 1000"
array teorico[3] = [75, 51, 32]

file_exists(file ) = system("[ -f '".file."' ] && echo '1' || echo '0'") + 0

set palette defined ( 0 "red", 1 "green")
set cbrange[0:1]
# color(y) = y >= 0 ? (255*65535) : (255*255)

set xlabel "Iteración"
set ylabel "Promedio Esperado"

dir = "graphs2"
system "mkdir ".dir

# set key outside;
set key right top;

i = 1;
set print "-"
do for [file in fileposfix]{
        do for [zvar in zvariance]{
        name="modSPC-".file."-".zvar
        filename = name.".txt"
        if (file_exists(filename)) {
            stats filename every ::::-1 u 1:3 nooutput
            max_blocks = STATS_blocks
            array titulo[max_blocks]
            set title "Mejor S para P(C) con X-Y-Z igual a ".file."-".zvar
            print "Targetting: ".filename
            outname = dir."/".name.".png"
            set output outname
            do for[blk=0:max_blocks-1]{
                stats filename i blk u 1:2 nooutput
                titulo[blk+1]=sprintf("%d",STATS_mean_x)." Veces"
            }
            plot for[blk=0:max_blocks-1] filename i blk u :2 w lp lw 1.5 t titulo[blk+1], teorico[i] lw 2 lt -1 t "Óptimo real"
            unset title
        }
    }
    i = i + 1
}
