## \file problem3.tcl
# Problem Statement 3 : Demonstrating Star Topology
#\verbatim

set ns [new Simulator]

$ns color 0 Red
$ns color 1 Green
$ns color 2 Coral
$ns color 3 Blue
$ns color 4 Azure

set f [open problem3.nam w]
$ns namtrace-all $f

proc finish {} {
    global ns f
    $ns flush-trace
    close $f
    
    exec nam problem3.nam &
    exit 0
}
puts "Enter no. of Nodes: "
gets stdin N
set n(0) [$ns node]
for {set i 1} {$i < $N} {incr i} {
    set n($i) [$ns node]
    $ns duplex-link $n($i) $n(0) 1Mb 10ms DropTail
}
puts "Enter k: "
gets stdin k
for {set i 0} {$i < $k} {incr i} {
    gets stdin i1
    gets stdin i2
    set tcp [new Agent/TCP]
    $tcp set class_ [expr ($i+1)%5]
    $ns attach-agent $n($i1) $tcp

    set sink [new Agent/TCPSink]
    $ns attach-agent $n($i2) $sink
    $ns connect $tcp $sink
    $tcp set fid_ $i

    set ftp($i) [new Application/FTP]
    $ftp($i) attach-agent $tcp
    $ftp($i) set type_ FTP
}

for {set i 0} {$i < $k} {incr i} {
    $ns at [expr ($i/10)+0.1] "$ftp($i) start"
    $ns at [expr ($i/10)+1.5] "$ftp($i) stop"
}
$ns at [expr ($k/10)+1.5] "finish"

$ns run