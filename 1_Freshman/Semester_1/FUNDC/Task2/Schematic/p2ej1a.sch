<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="Z" />
        <signal name="E" />
        <signal name="A" />
        <signal name="B" />
        <signal name="D" />
        <signal name="XLXN_29" />
        <signal name="XLXN_30" />
        <signal name="XLXN_35" />
        <signal name="C" />
        <signal name="XLXN_37" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="D" />
        <port polarity="Input" name="C" />
        <blockdef name="m4_1e">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="96" y1="-416" y2="-416" x1="0" />
            <line x2="96" y1="-352" y2="-352" x1="0" />
            <line x2="96" y1="-288" y2="-288" x1="0" />
            <line x2="96" y1="-224" y2="-224" x1="0" />
            <line x2="96" y1="-32" y2="-32" x1="0" />
            <line x2="256" y1="-320" y2="-320" x1="320" />
            <line x2="96" y1="-160" y2="-160" x1="0" />
            <line x2="96" y1="-96" y2="-96" x1="0" />
            <line x2="96" y1="-96" y2="-96" x1="176" />
            <line x2="176" y1="-208" y2="-96" x1="176" />
            <line x2="96" y1="-32" y2="-32" x1="224" />
            <line x2="224" y1="-216" y2="-32" x1="224" />
            <line x2="96" y1="-224" y2="-192" x1="256" />
            <line x2="256" y1="-416" y2="-224" x1="256" />
            <line x2="256" y1="-448" y2="-416" x1="96" />
            <line x2="96" y1="-192" y2="-448" x1="96" />
            <line x2="96" y1="-160" y2="-160" x1="128" />
            <line x2="128" y1="-200" y2="-160" x1="128" />
        </blockdef>
        <blockdef name="and2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
        </blockdef>
        <blockdef name="nor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="216" y1="-96" y2="-96" x1="256" />
            <circle r="12" cx="204" cy="-96" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <block symbolname="m4_1e" name="XLXI_1">
            <blockpin signalname="XLXN_30" name="D0" />
            <blockpin signalname="C" name="D1" />
            <blockpin signalname="XLXN_35" name="D2" />
            <blockpin signalname="D" name="D3" />
            <blockpin signalname="E" name="E" />
            <blockpin signalname="B" name="S0" />
            <blockpin signalname="A" name="S1" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_3">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="XLXN_30" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_4">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="XLXN_35" name="O" />
        </block>
        <block symbolname="vcc" name="XLXI_5">
            <blockpin signalname="E" name="P" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1424" y="1456" name="XLXI_1" orien="R0" />
        <branch name="E">
            <wire x2="1200" y1="1408" y2="1424" x1="1200" />
            <wire x2="1424" y1="1424" y2="1424" x1="1200" />
        </branch>
        <branch name="A">
            <wire x2="1424" y1="1360" y2="1360" x1="1392" />
        </branch>
        <iomarker fontsize="28" x="1392" y="1360" name="A" orien="R180" />
        <branch name="B">
            <wire x2="1424" y1="1296" y2="1296" x1="1392" />
        </branch>
        <iomarker fontsize="28" x="1392" y="1296" name="B" orien="R180" />
        <iomarker fontsize="28" x="752" y="960" name="D" orien="R270" />
        <iomarker fontsize="28" x="864" y="960" name="C" orien="R270" />
        <instance x="1136" y="1408" name="XLXI_5" orien="R0" />
        <branch name="D">
            <wire x2="752" y1="960" y2="1072" x1="752" />
            <wire x2="752" y1="1072" y2="1200" x1="752" />
            <wire x2="752" y1="1200" y2="1232" x1="752" />
            <wire x2="1424" y1="1232" y2="1232" x1="752" />
            <wire x2="1056" y1="1200" y2="1200" x1="752" />
            <wire x2="1056" y1="1072" y2="1072" x1="752" />
        </branch>
        <instance x="1056" y="1264" name="XLXI_4" orien="R0" />
        <instance x="1056" y="1136" name="XLXI_3" orien="R0" />
        <branch name="XLXN_30">
            <wire x2="1424" y1="1040" y2="1040" x1="1312" />
        </branch>
        <branch name="Z">
            <wire x2="1760" y1="1136" y2="1136" x1="1744" />
            <wire x2="1888" y1="1136" y2="1136" x1="1760" />
        </branch>
        <iomarker fontsize="28" x="1888" y="1136" name="Z" orien="R0" />
        <branch name="XLXN_35">
            <wire x2="1424" y1="1168" y2="1168" x1="1312" />
        </branch>
        <branch name="C">
            <wire x2="864" y1="960" y2="1008" x1="864" />
            <wire x2="864" y1="1008" y2="1104" x1="864" />
            <wire x2="1424" y1="1104" y2="1104" x1="864" />
            <wire x2="864" y1="1104" y2="1136" x1="864" />
            <wire x2="1056" y1="1136" y2="1136" x1="864" />
            <wire x2="1056" y1="1008" y2="1008" x1="864" />
        </branch>
    </sheet>
</drawing>