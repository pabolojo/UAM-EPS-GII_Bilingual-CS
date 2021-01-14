<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="Z" />
        <signal name="XLXN_19" />
        <signal name="XLXN_20" />
        <signal name="XLXN_21" />
        <signal name="XLXN_33" />
        <signal name="A" />
        <signal name="XLXN_40" />
        <signal name="B" />
        <signal name="C" />
        <signal name="XLXN_44" />
        <signal name="D" />
        <signal name="XLXN_46" />
        <signal name="XLXN_47" />
        <signal name="XLXN_48" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="D" />
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
        <blockdef name="or2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
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
        <block symbolname="m4_1e" name="XLXI_1">
            <blockpin signalname="C" name="D0" />
            <blockpin signalname="D" name="D1" />
            <blockpin signalname="C" name="D2" />
            <blockpin signalname="C" name="D3" />
            <blockpin signalname="XLXN_21" name="E" />
            <blockpin signalname="C" name="S0" />
            <blockpin signalname="B" name="S1" />
            <blockpin signalname="XLXN_19" name="O" />
        </block>
        <block symbolname="m4_1e" name="XLXI_2">
            <blockpin signalname="XLXN_33" name="D0" />
            <blockpin signalname="B" name="D1" />
            <blockpin signalname="D" name="D2" />
            <blockpin signalname="D" name="D3" />
            <blockpin signalname="A" name="E" />
            <blockpin signalname="C" name="S0" />
            <blockpin signalname="B" name="S1" />
            <blockpin signalname="XLXN_20" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_7">
            <blockpin signalname="XLXN_20" name="I0" />
            <blockpin signalname="XLXN_19" name="I1" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_8">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_21" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_9">
            <blockpin signalname="D" name="I" />
            <blockpin signalname="XLXN_33" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1584" y="960" name="XLXI_1" orien="R0" />
        <instance x="1584" y="1584" name="XLXI_2" orien="R0" />
        <branch name="Z">
            <wire x2="2464" y1="960" y2="960" x1="2336" />
            <wire x2="2496" y1="960" y2="960" x1="2464" />
        </branch>
        <iomarker fontsize="28" x="2496" y="960" name="Z" orien="R0" />
        <instance x="2080" y="1056" name="XLXI_7" orien="R0" />
        <branch name="XLXN_19">
            <wire x2="1984" y1="640" y2="640" x1="1904" />
            <wire x2="1984" y1="640" y2="928" x1="1984" />
            <wire x2="2080" y1="928" y2="928" x1="1984" />
        </branch>
        <branch name="XLXN_20">
            <wire x2="1984" y1="1264" y2="1264" x1="1904" />
            <wire x2="1984" y1="992" y2="1264" x1="1984" />
            <wire x2="2080" y1="992" y2="992" x1="1984" />
        </branch>
        <branch name="XLXN_21">
            <wire x2="1584" y1="928" y2="928" x1="1552" />
        </branch>
        <instance x="1328" y="960" name="XLXI_8" orien="R0" />
        <branch name="XLXN_33">
            <wire x2="1584" y1="1168" y2="1168" x1="1552" />
        </branch>
        <instance x="1328" y="1200" name="XLXI_9" orien="R0" />
        <iomarker fontsize="28" x="880" y="480" name="A" orien="R270" />
        <iomarker fontsize="28" x="960" y="480" name="B" orien="R270" />
        <iomarker fontsize="28" x="1040" y="480" name="C" orien="R270" />
        <iomarker fontsize="28" x="1120" y="480" name="D" orien="R270" />
        <branch name="A">
            <wire x2="880" y1="480" y2="928" x1="880" />
            <wire x2="1328" y1="928" y2="928" x1="880" />
            <wire x2="880" y1="928" y2="1552" x1="880" />
            <wire x2="1584" y1="1552" y2="1552" x1="880" />
        </branch>
        <branch name="B">
            <wire x2="960" y1="480" y2="864" x1="960" />
            <wire x2="1584" y1="864" y2="864" x1="960" />
            <wire x2="960" y1="864" y2="1232" x1="960" />
            <wire x2="960" y1="1232" y2="1488" x1="960" />
            <wire x2="1584" y1="1488" y2="1488" x1="960" />
            <wire x2="1584" y1="1232" y2="1232" x1="960" />
        </branch>
        <branch name="C">
            <wire x2="1040" y1="480" y2="544" x1="1040" />
            <wire x2="1584" y1="544" y2="544" x1="1040" />
            <wire x2="1040" y1="544" y2="672" x1="1040" />
            <wire x2="1584" y1="672" y2="672" x1="1040" />
            <wire x2="1040" y1="672" y2="736" x1="1040" />
            <wire x2="1040" y1="736" y2="800" x1="1040" />
            <wire x2="1584" y1="800" y2="800" x1="1040" />
            <wire x2="1040" y1="800" y2="1424" x1="1040" />
            <wire x2="1584" y1="1424" y2="1424" x1="1040" />
            <wire x2="1584" y1="736" y2="736" x1="1040" />
        </branch>
        <branch name="D">
            <wire x2="1120" y1="480" y2="608" x1="1120" />
            <wire x2="1584" y1="608" y2="608" x1="1120" />
            <wire x2="1120" y1="608" y2="1168" x1="1120" />
            <wire x2="1328" y1="1168" y2="1168" x1="1120" />
            <wire x2="1120" y1="1168" y2="1296" x1="1120" />
            <wire x2="1584" y1="1296" y2="1296" x1="1120" />
            <wire x2="1120" y1="1296" y2="1360" x1="1120" />
            <wire x2="1584" y1="1360" y2="1360" x1="1120" />
        </branch>
    </sheet>
</drawing>