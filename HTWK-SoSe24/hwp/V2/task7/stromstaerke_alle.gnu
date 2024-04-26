set datafile separator ","
set terminal pngcairo size 1600,1200 enhanced font 'Verdana,20'
set output 'neu.png'

# Titel und Achsenbeschriftungen
set title "Aufgabe 7.5"
set ylabel "I in Milliampere"
set xlabel "U in Volt"
set autoscale


# Plot-Befehl für die Daten
plot 'D1_sperr_result_diode.csv' using 4:2 with lines linewidth 3 title "Diode 1", \
     'D2_sperr_result_diode.csv' using 4:2 with lines linewidth 3 title "Diode 2", \
     'D3_sperr_result_diode.csv' using 4:2 with lines linewidth 3 title "Diode 3", \
     'D4_sperr_result_diode.csv' using 4:2 with lines linewidth 3 title "Diode 4", \
     'D5_sperr_result_diode.csv' using 4:2 with lines linewidth 3 title "Diode 5", \
     'D6_sperr_result_diode.csv' using 4:2 with lines linewidth 3 title "Diode 6"
