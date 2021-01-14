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
        <signal name="B" />
        <signal name="A" />
        <signal name="C" />
        <signal name="Z" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="C" />
        <port polarity="Output" name="Z" />
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
        <blockdef name="nand2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="216" y1="-96" y2="-96" x1="256" />
            <circle r="12" cx="204" cy="-96" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
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
        <block symbolname="and2" name="XLXI_1">
            <blockpin signalname="XLXN_4" name="I0" />
            <blockpin signalname="XLXN_3" name="I1" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_2">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_3">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="XLXN_1" name="I1" />
            <blockpin signalname="XLXN_4" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_4">
            <blockpin signalname="B" name="I" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1632" y="1216" name="XLXI_1" orien="R0" />
        <instance x="944" y="1120" name="XLXI_2" orien="R0" />
        <instance x="960" y="1488" name="XLXI_3" orien="R0" />
        <instance x="640" y="1280" name="XLXI_4" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="912" y1="1248" y2="1248" x1="864" />
            <wire x2="912" y1="1248" y2="1360" x1="912" />
            <wire x2="960" y1="1360" y2="1360" x1="912" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1216" y1="1024" y2="1024" x1="1200" />
            <wire x2="1216" y1="1024" y2="1088" x1="1216" />
            <wire x2="1632" y1="1088" y2="1088" x1="1216" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="1424" y1="1392" y2="1392" x1="1216" />
            <wire x2="1424" y1="1152" y2="1392" x1="1424" />
            <wire x2="1632" y1="1152" y2="1152" x1="1424" />
        </branch>
        <branch name="B">
            <wire x2="640" y1="1056" y2="1056" x1="432" />
            <wire x2="944" y1="1056" y2="1056" x1="640" />
            <wire x2="640" y1="1056" y2="1072" x1="640" />
            <wire x2="640" y1="1072" y2="1072" x1="560" />
            <wire x2="560" y1="1072" y2="1248" x1="560" />
            <wire x2="640" y1="1248" y2="1248" x1="560" />
        </branch>
        <branch name="A">
            <wire x2="432" y1="928" y2="992" x1="432" />
            <wire x2="944" y1="992" y2="992" x1="432" />
        </branch>
        <branch name="C">
            <wire x2="464" y1="1408" y2="1424" x1="464" />
            <wire x2="960" y1="1424" y2="1424" x1="464" />
        </branch>
        <iomarker fontsize="28" x="464" y="1408" name="C" orien="R270" />
        <iomarker fontsize="28" x="432" y="1056" name="B" orien="R180" />
        <iomarker fontsize="28" x="432" y="928" name="A" orien="R270" />
        <branch name="Z">
            <wire x2="1920" y1="1120" y2="1120" x1="1888" />
        </branch>
        <iomarker fontsize="28" x="1920" y="1120" name="Z" orien="R0" />
    </sheet>
</drawing>