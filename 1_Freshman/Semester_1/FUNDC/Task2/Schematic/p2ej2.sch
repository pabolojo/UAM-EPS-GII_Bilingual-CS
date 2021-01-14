<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_3" />
        <signal name="XLXN_9" />
        <signal name="C" />
        <signal name="D" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="Z" />
        <signal name="XLXN_17" />
        <signal name="B" />
        <signal name="XLXN_19" />
        <signal name="XLXN_20" />
        <signal name="A" />
        <signal name="XLXN_22" />
        <signal name="XLXN_23" />
        <signal name="XLXN_24" />
        <signal name="XLXN_25" />
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="D" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="A" />
        <blockdef name="d3_8e">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="320" y1="-576" y2="-576" x1="384" />
            <line x2="320" y1="-512" y2="-512" x1="384" />
            <line x2="320" y1="-448" y2="-448" x1="384" />
            <line x2="320" y1="-384" y2="-384" x1="384" />
            <line x2="320" y1="-320" y2="-320" x1="384" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
            <rect width="256" x="64" y="-640" height="576" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
        </blockdef>
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <blockdef name="or6">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="48" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-320" y2="-320" x1="0" />
            <line x2="48" y1="-384" y2="-384" x1="0" />
            <line x2="192" y1="-224" y2="-224" x1="256" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <arc ex="112" ey="-272" sx="192" sy="-224" r="88" cx="116" cy="-184" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
            <arc ex="192" ey="-224" sx="112" sy="-176" r="88" cx="116" cy="-264" />
            <arc ex="48" ey="-272" sx="48" sy="-176" r="56" cx="16" cy="-224" />
            <line x2="48" y1="-272" y2="-272" x1="112" />
            <line x2="48" y1="-64" y2="-176" x1="48" />
            <line x2="48" y1="-272" y2="-384" x1="48" />
        </blockdef>
        <block symbolname="d3_8e" name="XLXI_1">
            <blockpin signalname="B" name="A0" />
            <blockpin signalname="C" name="A1" />
            <blockpin signalname="D" name="A2" />
            <blockpin signalname="XLXN_20" name="E" />
            <blockpin name="D0" />
            <blockpin name="D1" />
            <blockpin name="D2" />
            <blockpin signalname="XLXN_23" name="D3" />
            <blockpin name="D4" />
            <blockpin name="D5" />
            <blockpin signalname="XLXN_24" name="D6" />
            <blockpin signalname="XLXN_25" name="D7" />
        </block>
        <block symbolname="d3_8e" name="XLXI_2">
            <blockpin signalname="B" name="A0" />
            <blockpin signalname="C" name="A1" />
            <blockpin signalname="D" name="A2" />
            <blockpin signalname="A" name="E" />
            <blockpin signalname="XLXN_26" name="D0" />
            <blockpin name="D1" />
            <blockpin name="D2" />
            <blockpin name="D3" />
            <blockpin name="D4" />
            <blockpin signalname="XLXN_28" name="D5" />
            <blockpin name="D6" />
            <blockpin signalname="XLXN_27" name="D7" />
        </block>
        <block symbolname="inv" name="XLXI_5">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_20" name="O" />
        </block>
        <block symbolname="or6" name="XLXI_6">
            <blockpin signalname="XLXN_27" name="I0" />
            <blockpin signalname="XLXN_28" name="I1" />
            <blockpin signalname="XLXN_26" name="I2" />
            <blockpin signalname="XLXN_25" name="I3" />
            <blockpin signalname="XLXN_24" name="I4" />
            <blockpin signalname="XLXN_23" name="I5" />
            <blockpin signalname="Z" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1344" y="1216" name="XLXI_1" orien="R0" />
        <instance x="1344" y="1920" name="XLXI_2" orien="R0" />
        <branch name="C">
            <wire x2="928" y1="560" y2="704" x1="928" />
            <wire x2="1344" y1="704" y2="704" x1="928" />
            <wire x2="928" y1="704" y2="1408" x1="928" />
            <wire x2="1344" y1="1408" y2="1408" x1="928" />
        </branch>
        <branch name="D">
            <wire x2="1040" y1="560" y2="768" x1="1040" />
            <wire x2="1344" y1="768" y2="768" x1="1040" />
            <wire x2="1040" y1="768" y2="1472" x1="1040" />
            <wire x2="1344" y1="1472" y2="1472" x1="1040" />
        </branch>
        <iomarker fontsize="28" x="928" y="560" name="C" orien="R270" />
        <iomarker fontsize="28" x="1040" y="560" name="D" orien="R270" />
        <branch name="Z">
            <wire x2="2544" y1="1232" y2="1232" x1="2512" />
        </branch>
        <iomarker fontsize="28" x="2544" y="1232" name="Z" orien="R0" />
        <iomarker fontsize="28" x="640" y="560" name="A" orien="R270" />
        <branch name="B">
            <wire x2="816" y1="560" y2="640" x1="816" />
            <wire x2="1344" y1="640" y2="640" x1="816" />
            <wire x2="816" y1="640" y2="1344" x1="816" />
            <wire x2="1344" y1="1344" y2="1344" x1="816" />
        </branch>
        <iomarker fontsize="28" x="816" y="560" name="B" orien="R270" />
        <branch name="XLXN_20">
            <wire x2="1344" y1="1088" y2="1088" x1="1312" />
        </branch>
        <instance x="1088" y="1120" name="XLXI_5" orien="R0" />
        <branch name="A">
            <wire x2="640" y1="560" y2="1088" x1="640" />
            <wire x2="1088" y1="1088" y2="1088" x1="640" />
            <wire x2="640" y1="1088" y2="1792" x1="640" />
            <wire x2="1344" y1="1792" y2="1792" x1="640" />
        </branch>
        <instance x="2256" y="1456" name="XLXI_6" orien="R0" />
        <branch name="XLXN_23">
            <wire x2="2256" y1="832" y2="832" x1="1728" />
            <wire x2="2256" y1="832" y2="1072" x1="2256" />
        </branch>
        <branch name="XLXN_24">
            <wire x2="1984" y1="1024" y2="1024" x1="1728" />
            <wire x2="1984" y1="1024" y2="1136" x1="1984" />
            <wire x2="2256" y1="1136" y2="1136" x1="1984" />
        </branch>
        <branch name="XLXN_25">
            <wire x2="1968" y1="1088" y2="1088" x1="1728" />
            <wire x2="1968" y1="1088" y2="1200" x1="1968" />
            <wire x2="2256" y1="1200" y2="1200" x1="1968" />
        </branch>
        <branch name="XLXN_26">
            <wire x2="1984" y1="1344" y2="1344" x1="1728" />
            <wire x2="1984" y1="1264" y2="1344" x1="1984" />
            <wire x2="2256" y1="1264" y2="1264" x1="1984" />
        </branch>
        <branch name="XLXN_27">
            <wire x2="2256" y1="1792" y2="1792" x1="1728" />
            <wire x2="2256" y1="1392" y2="1792" x1="2256" />
        </branch>
        <branch name="XLXN_28">
            <wire x2="2000" y1="1664" y2="1664" x1="1728" />
            <wire x2="2000" y1="1328" y2="1664" x1="2000" />
            <wire x2="2256" y1="1328" y2="1328" x1="2000" />
        </branch>
    </sheet>
</drawing>