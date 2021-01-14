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
        <signal name="XLXN_8" />
        <signal name="XLXN_10" />
        <signal name="XLXN_11" />
        <signal name="A" />
        <signal name="B" />
        <signal name="C" />
        <signal name="D" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="D" />
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
        <blockdef name="and3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
        </blockdef>
        <blockdef name="or4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="48" y1="-256" y2="-256" x1="0" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <arc ex="112" ey="-208" sx="192" sy="-160" r="88" cx="116" cy="-120" />
            <line x2="48" y1="-208" y2="-208" x1="112" />
            <line x2="48" y1="-112" y2="-112" x1="112" />
            <line x2="48" y1="-256" y2="-208" x1="48" />
            <line x2="48" y1="-64" y2="-112" x1="48" />
            <arc ex="48" ey="-208" sx="48" sy="-112" r="56" cx="16" cy="-160" />
            <arc ex="192" ey="-160" sx="112" sy="-112" r="88" cx="116" cy="-200" />
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
        <block symbolname="and4" name="XLXI_1">
            <blockpin signalname="XLXN_11" name="I0" />
            <blockpin signalname="XLXN_10" name="I1" />
            <blockpin signalname="XLXN_8" name="I2" />
            <blockpin signalname="A" name="I3" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="and4" name="XLXI_2">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="XLXN_10" name="I1" />
            <blockpin signalname="XLXN_8" name="I2" />
            <blockpin signalname="XLXN_6" name="I3" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_3">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="XLXN_6" name="I2" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_4">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="A" name="I2" />
            <blockpin signalname="XLXN_4" name="O" />
        </block>
        <block symbolname="or4" name="XLXI_5">
            <blockpin signalname="XLXN_4" name="I0" />
            <blockpin signalname="XLXN_3" name="I1" />
            <blockpin signalname="XLXN_2" name="I2" />
            <blockpin signalname="XLXN_1" name="I3" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_6">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_6" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_7">
            <blockpin signalname="B" name="I" />
            <blockpin signalname="XLXN_8" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_8">
            <blockpin signalname="C" name="I" />
            <blockpin signalname="XLXN_10" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_9">
            <blockpin signalname="D" name="I" />
            <blockpin signalname="XLXN_11" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="944" y="1216" name="XLXI_1" orien="R0" />
        <instance x="944" y="1504" name="XLXI_2" orien="R0" />
        <instance x="944" y="1728" name="XLXI_3" orien="R0" />
        <instance x="944" y="1936" name="XLXI_4" orien="R0" />
        <instance x="1872" y="1552" name="XLXI_5" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="1872" y1="1056" y2="1056" x1="1200" />
            <wire x2="1872" y1="1056" y2="1296" x1="1872" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1536" y1="1344" y2="1344" x1="1200" />
            <wire x2="1536" y1="1344" y2="1360" x1="1536" />
            <wire x2="1872" y1="1360" y2="1360" x1="1536" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1536" y1="1600" y2="1600" x1="1200" />
            <wire x2="1536" y1="1424" y2="1600" x1="1536" />
            <wire x2="1872" y1="1424" y2="1424" x1="1536" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="1872" y1="1808" y2="1808" x1="1200" />
            <wire x2="1872" y1="1488" y2="1808" x1="1872" />
        </branch>
        <branch name="Z">
            <wire x2="2160" y1="1392" y2="1392" x1="2128" />
        </branch>
        <iomarker fontsize="28" x="2160" y="1392" name="Z" orien="R0" />
        <instance x="288" y="1008" name="XLXI_6" orien="R0" />
        <instance x="288" y="1296" name="XLXI_7" orien="R0" />
        <instance x="288" y="1520" name="XLXI_8" orien="R0" />
        <instance x="304" y="1728" name="XLXI_9" orien="R0" />
        <branch name="XLXN_6">
            <wire x2="720" y1="976" y2="976" x1="512" />
            <wire x2="720" y1="976" y2="1248" x1="720" />
            <wire x2="720" y1="1248" y2="1264" x1="720" />
            <wire x2="720" y1="1264" y2="1536" x1="720" />
            <wire x2="944" y1="1536" y2="1536" x1="720" />
            <wire x2="944" y1="1248" y2="1248" x1="720" />
        </branch>
        <branch name="XLXN_8">
            <wire x2="640" y1="1264" y2="1264" x1="512" />
            <wire x2="704" y1="1264" y2="1264" x1="640" />
            <wire x2="640" y1="1264" y2="1312" x1="640" />
            <wire x2="944" y1="1312" y2="1312" x1="640" />
            <wire x2="704" y1="1024" y2="1264" x1="704" />
            <wire x2="944" y1="1024" y2="1024" x1="704" />
        </branch>
        <branch name="XLXN_10">
            <wire x2="608" y1="1488" y2="1488" x1="512" />
            <wire x2="688" y1="1488" y2="1488" x1="608" />
            <wire x2="944" y1="1376" y2="1376" x1="608" />
            <wire x2="608" y1="1376" y2="1488" x1="608" />
            <wire x2="688" y1="1088" y2="1488" x1="688" />
            <wire x2="944" y1="1088" y2="1088" x1="688" />
        </branch>
        <branch name="XLXN_11">
            <wire x2="736" y1="1696" y2="1696" x1="528" />
            <wire x2="736" y1="1152" y2="1696" x1="736" />
            <wire x2="944" y1="1152" y2="1152" x1="736" />
        </branch>
        <branch name="A">
            <wire x2="192" y1="976" y2="976" x1="128" />
            <wire x2="240" y1="976" y2="976" x1="192" />
            <wire x2="288" y1="976" y2="976" x1="240" />
            <wire x2="192" y1="976" y2="1744" x1="192" />
            <wire x2="944" y1="1744" y2="1744" x1="192" />
            <wire x2="240" y1="928" y2="976" x1="240" />
            <wire x2="944" y1="928" y2="928" x1="240" />
            <wire x2="944" y1="928" y2="960" x1="944" />
        </branch>
        <branch name="B">
            <wire x2="240" y1="1264" y2="1264" x1="144" />
            <wire x2="288" y1="1264" y2="1264" x1="240" />
            <wire x2="240" y1="1264" y2="1600" x1="240" />
            <wire x2="608" y1="1600" y2="1600" x1="240" />
            <wire x2="944" y1="1600" y2="1600" x1="608" />
            <wire x2="608" y1="1600" y2="1808" x1="608" />
            <wire x2="944" y1="1808" y2="1808" x1="608" />
        </branch>
        <branch name="C">
            <wire x2="224" y1="1488" y2="1488" x1="160" />
            <wire x2="288" y1="1488" y2="1488" x1="224" />
            <wire x2="224" y1="1488" y2="1584" x1="224" />
            <wire x2="592" y1="1584" y2="1584" x1="224" />
            <wire x2="592" y1="1584" y2="1664" x1="592" />
            <wire x2="944" y1="1664" y2="1664" x1="592" />
        </branch>
        <branch name="D">
            <wire x2="256" y1="1696" y2="1696" x1="176" />
            <wire x2="304" y1="1696" y2="1696" x1="256" />
            <wire x2="256" y1="1696" y2="1872" x1="256" />
            <wire x2="816" y1="1872" y2="1872" x1="256" />
            <wire x2="944" y1="1872" y2="1872" x1="816" />
            <wire x2="944" y1="1440" y2="1440" x1="816" />
            <wire x2="816" y1="1440" y2="1872" x1="816" />
        </branch>
        <iomarker fontsize="28" x="128" y="976" name="A" orien="R180" />
        <iomarker fontsize="28" x="144" y="1264" name="B" orien="R180" />
        <iomarker fontsize="28" x="160" y="1488" name="C" orien="R180" />
        <iomarker fontsize="28" x="176" y="1696" name="D" orien="R180" />
    </sheet>
</drawing>