set terminal tikz
set output "graph.tex"
set xr[-5:5]
set title "Example"
plot sin(x) t "$\\sin(x)$", cos(x) t "$\\cos(x)$", sin(x)+cos(x) t "Combined"