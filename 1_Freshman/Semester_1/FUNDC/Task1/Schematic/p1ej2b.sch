<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="XLXN_2" />
        <signal name="XLXN_3" />
        <signal name="XLXN_4" />
        <signal name="Z" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="XLXN_11" />
        <signal name="XLXN_12" />
        <signal name="A" />
        <signal name="B" />
        <signal name="C" />
        <signal name="D" />
        <signal name="XLXN_17" />
        <signal name="XLXN_18" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="D" />
        <blockdef name="or3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="72" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <arc ex="192" ey="-128" sx="112" sy="-80" r="88" cx="116" cy="-168" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <line x2="48" y1="-80" y2="-80" x1="112" />
            <arc ex="112" ey="-176" sx="192" sy="-128" r="88" cx="116" cy="-88" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
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
        <blockdef name="and4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-112" y2="-112" x1="144" />
            <arc ex="144" ey="-208" sx="144" sy="-112" r="48" cx="144" cy="-160" />
            <line x2="144" y1="-208" y2="-208" x1="64" />
            <line x2="64" y1="-64" y2="-256" x1="64" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-64" y2="-64" x1="0" />
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
        <block symbolname="or3" name="XLXI_1">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="XLXN_12" name="I1" />
            <blockpin signalname="XLXN_7" name="I2" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_2">
            <blockpin signalname="XLXN_11" name="I0" />
            <blockpin signalname="XLXN_7" name="I1" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_3">
            <blockpin signalname="XLXN_11" name="I0" />
            <blockpin signalname="XLXN_9" name="I1" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_4">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="XLXN_9" name="I1" />
            <blockpin signalname="XLXN_4" name="O" />
        </block>
        <block symbolname="and4" name="XLXI_5">
            <blockpin signalname="XLXN_4" name="I0" />
            <blockpin signalname="XLXN_3" name="I1" />
            <blockpin signalname="XLXN_2" name="I2" />
            <blockpin signalname="XLXN_1" name="I3" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_6">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_7" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_7">
            <blockpin signalname="B" name="I" />
            <blockpin signalname="XLXN_9" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_8">
            <blockpin signalname="C" name="I" />
            <blockpin signalname="XLXN_11" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_9">
            <blockpin signalname="D" name="I" />
            <blockpin signalname="XLXN_12" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1360" y="880" name="XLXI_1" orien="R0" />
        <instance x="1408" y="1200" name="XLXI_2" orien="R0" />
        <instance x="1392" y="1488" name="XLXI_3" orien="R0" />
        <instance x="1392" y="1792" name="XLXI_4" orien="R0" />
        <instance x="2160" y="1344" name="XLXI_5" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="2160" y1="752" y2="752" x1="1616" />
            <wire x2="2160" y1="752" y2="1088" x1="2160" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1904" y1="1104" y2="1104" x1="1664" />
            <wire x2="1904" y1="1104" y2="1152" x1="1904" />
            <wire x2="2160" y1="1152" y2="1152" x1="1904" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1904" y1="1392" y2="1392" x1="1648" />
            <wire x2="1904" y1="1216" y2="1392" x1="1904" />
            <wire x2="2160" y1="1216" y2="1216" x1="1904" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="2160" y1="1696" y2="1696" x1="1648" />
            <wire x2="2160" y1="1280" y2="1696" x1="2160" />
        </branch>
        <branch name="Z">
            <wire x2="2688" y1="1184" y2="1184" x1="2416" />
        </branch>
        <instance x="528" y="768" name="XLXI_6" orien="R0" />
        <instance x="560" y="1040" name="XLXI_7" orien="R0" />
        <instance x="560" y="1248" name="XLXI_8" orien="R0" />
        <instance x="560" y="1504" name="XLXI_9" orien="R0" />
        <branch name="XLXN_7">
            <wire x2="976" y1="736" y2="736" x1="752" />
            <wire x2="1056" y1="736" y2="736" x1="976" />
            <wire x2="976" y1="736" y2="1072" x1="976" />
            <wire x2="1408" y1="1072" y2="1072" x1="976" />
            <wire x2="1056" y1="688" y2="736" x1="1056" />
            <wire x2="1360" y1="688" y2="688" x1="1056" />
        </branch>
        <branch name="XLXN_9">
            <wire x2="896" y1="1008" y2="1008" x1="784" />
            <wire x2="1088" y1="1008" y2="1008" x1="896" />
            <wire x2="1088" y1="1008" y2="1360" x1="1088" />
            <wire x2="1392" y1="1360" y2="1360" x1="1088" />
            <wire x2="896" y1="1008" y2="1664" x1="896" />
            <wire x2="1392" y1="1664" y2="1664" x1="896" />
        </branch>
        <branch name="XLXN_11">
            <wire x2="944" y1="1216" y2="1216" x1="784" />
            <wire x2="1072" y1="1216" y2="1216" x1="944" />
            <wire x2="944" y1="1216" y2="1424" x1="944" />
            <wire x2="1392" y1="1424" y2="1424" x1="944" />
            <wire x2="1072" y1="1136" y2="1216" x1="1072" />
            <wire x2="1408" y1="1136" y2="1136" x1="1072" />
        </branch>
        <branch name="XLXN_12">
            <wire x2="1056" y1="1472" y2="1472" x1="784" />
            <wire x2="1056" y1="752" y2="1472" x1="1056" />
            <wire x2="1360" y1="752" y2="752" x1="1056" />
        </branch>
        <branch name="A">
            <wire x2="528" y1="736" y2="736" x1="256" />
        </branch>
        <branch name="B">
            <wire x2="464" y1="1008" y2="1008" x1="288" />
            <wire x2="560" y1="1008" y2="1008" x1="464" />
            <wire x2="1360" y1="816" y2="816" x1="464" />
            <wire x2="464" y1="816" y2="1008" x1="464" />
        </branch>
        <branch name="C">
            <wire x2="560" y1="1216" y2="1216" x1="304" />
        </branch>
        <branch name="D">
            <wire x2="496" y1="1472" y2="1472" x1="288" />
            <wire x2="560" y1="1472" y2="1472" x1="496" />
            <wire x2="496" y1="1472" y2="1728" x1="496" />
            <wire x2="1392" y1="1728" y2="1728" x1="496" />
        </branch>
        <iomarker fontsize="28" x="256" y="736" name="A" orien="R180" />
        <iomarker fontsize="28" x="288" y="1008" name="B" orien="R180" />
        <iomarker fontsize="28" x="304" y="1216" name="C" orien="R180" />
        <iomarker fontsize="28" x="288" y="1472" name="D" orien="R180" />
        <iomarker fontsize="28" x="2688" y="1184" name="Z" orien="R0" />
    </sheet>
</drawing>