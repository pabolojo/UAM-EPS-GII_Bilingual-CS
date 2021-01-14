<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xbr" name="DeviceFamilyName">
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
        <signal name="XLXN_11" />
        <signal name="B" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="XLXN_17" />
        <signal name="XLXN_18" />
        <signal name="XLXN_19" />
        <signal name="XLXN_20" />
        <signal name="A" />
        <signal name="C" />
        <signal name="XLXN_23" />
        <signal name="D" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="D" />
        <blockdef name="nand4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="216" y1="-160" y2="-160" x1="256" />
            <circle r="12" cx="204" cy="-160" />
            <line x2="64" y1="-64" y2="-256" x1="64" />
            <line x2="144" y1="-208" y2="-208" x1="64" />
            <arc ex="144" ey="-208" sx="144" sy="-112" r="48" cx="144" cy="-160" />
            <line x2="64" y1="-112" y2="-112" x1="144" />
        </blockdef>
        <blockdef name="nand3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="216" y1="-128" y2="-128" x1="256" />
            <circle r="12" cx="204" cy="-128" />
            <line x2="144" y1="-176" y2="-176" x1="64" />
            <line x2="64" y1="-80" y2="-80" x1="144" />
            <arc ex="144" ey="-176" sx="144" sy="-80" r="48" cx="144" cy="-128" />
            <line x2="64" y1="-64" y2="-192" x1="64" />
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
        <block symbolname="nand4" name="XLXI_1">
            <blockpin signalname="XLXN_20" name="I0" />
            <blockpin signalname="XLXN_19" name="I1" />
            <blockpin signalname="XLXN_18" name="I2" />
            <blockpin signalname="A" name="I3" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="nand4" name="XLXI_2">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="XLXN_19" name="I1" />
            <blockpin signalname="XLXN_18" name="I2" />
            <blockpin signalname="XLXN_17" name="I3" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="nand3" name="XLXI_3">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="XLXN_17" name="I2" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="nand3" name="XLXI_4">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="A" name="I2" />
            <blockpin signalname="XLXN_4" name="O" />
        </block>
        <block symbolname="nand4" name="XLXI_5">
            <blockpin signalname="XLXN_4" name="I0" />
            <blockpin signalname="XLXN_3" name="I1" />
            <blockpin signalname="XLXN_2" name="I2" />
            <blockpin signalname="XLXN_1" name="I3" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_6">
            <blockpin signalname="A" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="XLXN_17" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_7">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="XLXN_18" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_8">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="C" name="I1" />
            <blockpin signalname="XLXN_19" name="O" />
        </block>
        <block symbolname="nand2" name="XLXI_9">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="D" name="I1" />
            <blockpin signalname="XLXN_20" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1184" y="896" name="XLXI_1" orien="R0" />
        <instance x="1184" y="1232" name="XLXI_2" orien="R0" />
        <instance x="1184" y="1488" name="XLXI_3" orien="R0" />
        <instance x="1184" y="1744" name="XLXI_4" orien="R0" />
        <instance x="1728" y="1344" name="XLXI_5" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="1728" y1="736" y2="736" x1="1440" />
            <wire x2="1728" y1="736" y2="1088" x1="1728" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1584" y1="1072" y2="1072" x1="1440" />
            <wire x2="1584" y1="1072" y2="1152" x1="1584" />
            <wire x2="1728" y1="1152" y2="1152" x1="1584" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1584" y1="1360" y2="1360" x1="1440" />
            <wire x2="1584" y1="1216" y2="1360" x1="1584" />
            <wire x2="1728" y1="1216" y2="1216" x1="1584" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="1728" y1="1616" y2="1616" x1="1440" />
            <wire x2="1728" y1="1280" y2="1616" x1="1728" />
        </branch>
        <branch name="Z">
            <wire x2="2128" y1="1184" y2="1184" x1="1984" />
        </branch>
        <instance x="560" y="784" name="XLXI_6" orien="R0" />
        <instance x="560" y="1136" name="XLXI_7" orien="R0" />
        <instance x="560" y="1440" name="XLXI_8" orien="R0" />
        <instance x="560" y="1712" name="XLXI_9" orien="R0" />
        <branch name="B">
            <wire x2="400" y1="1040" y2="1040" x1="288" />
            <wire x2="480" y1="1040" y2="1040" x1="400" />
            <wire x2="544" y1="1040" y2="1040" x1="480" />
            <wire x2="544" y1="1040" y2="1072" x1="544" />
            <wire x2="560" y1="1072" y2="1072" x1="544" />
            <wire x2="400" y1="912" y2="1040" x1="400" />
            <wire x2="1056" y1="912" y2="912" x1="400" />
            <wire x2="1056" y1="912" y2="1616" x1="1056" />
            <wire x2="1184" y1="1616" y2="1616" x1="1056" />
            <wire x2="480" y1="928" y2="1040" x1="480" />
            <wire x2="896" y1="928" y2="928" x1="480" />
            <wire x2="896" y1="928" y2="1360" x1="896" />
            <wire x2="1184" y1="1360" y2="1360" x1="896" />
            <wire x2="560" y1="1008" y2="1008" x1="544" />
            <wire x2="544" y1="1008" y2="1040" x1="544" />
        </branch>
        <branch name="XLXN_17">
            <wire x2="992" y1="688" y2="688" x1="816" />
            <wire x2="992" y1="688" y2="976" x1="992" />
            <wire x2="1072" y1="976" y2="976" x1="992" />
            <wire x2="1184" y1="976" y2="976" x1="1072" />
            <wire x2="1072" y1="976" y2="1296" x1="1072" />
            <wire x2="1184" y1="1296" y2="1296" x1="1072" />
        </branch>
        <branch name="XLXN_18">
            <wire x2="912" y1="1040" y2="1040" x1="816" />
            <wire x2="976" y1="1040" y2="1040" x1="912" />
            <wire x2="912" y1="992" y2="1040" x1="912" />
            <wire x2="1040" y1="992" y2="992" x1="912" />
            <wire x2="1040" y1="992" y2="1040" x1="1040" />
            <wire x2="1184" y1="1040" y2="1040" x1="1040" />
            <wire x2="976" y1="704" y2="1040" x1="976" />
            <wire x2="1184" y1="704" y2="704" x1="976" />
        </branch>
        <branch name="XLXN_19">
            <wire x2="960" y1="1344" y2="1344" x1="816" />
            <wire x2="1184" y1="768" y2="768" x1="960" />
            <wire x2="960" y1="768" y2="1096" x1="960" />
            <wire x2="960" y1="1096" y2="1104" x1="960" />
            <wire x2="960" y1="1104" y2="1344" x1="960" />
            <wire x2="1184" y1="1104" y2="1104" x1="960" />
        </branch>
        <branch name="XLXN_20">
            <wire x2="944" y1="1616" y2="1616" x1="816" />
            <wire x2="944" y1="832" y2="1616" x1="944" />
            <wire x2="1184" y1="832" y2="832" x1="944" />
        </branch>
        <branch name="A">
            <wire x2="400" y1="688" y2="688" x1="288" />
            <wire x2="448" y1="688" y2="688" x1="400" />
            <wire x2="544" y1="688" y2="688" x1="448" />
            <wire x2="544" y1="688" y2="720" x1="544" />
            <wire x2="560" y1="720" y2="720" x1="544" />
            <wire x2="448" y1="688" y2="1552" x1="448" />
            <wire x2="1184" y1="1552" y2="1552" x1="448" />
            <wire x2="400" y1="624" y2="688" x1="400" />
            <wire x2="1184" y1="624" y2="624" x1="400" />
            <wire x2="1184" y1="624" y2="640" x1="1184" />
            <wire x2="560" y1="656" y2="656" x1="544" />
            <wire x2="544" y1="656" y2="688" x1="544" />
        </branch>
        <branch name="C">
            <wire x2="480" y1="1344" y2="1344" x1="288" />
            <wire x2="496" y1="1344" y2="1344" x1="480" />
            <wire x2="544" y1="1344" y2="1344" x1="496" />
            <wire x2="544" y1="1344" y2="1376" x1="544" />
            <wire x2="560" y1="1376" y2="1376" x1="544" />
            <wire x2="496" y1="1344" y2="1424" x1="496" />
            <wire x2="1184" y1="1424" y2="1424" x1="496" />
            <wire x2="560" y1="1312" y2="1312" x1="544" />
            <wire x2="544" y1="1312" y2="1344" x1="544" />
        </branch>
        <branch name="D">
            <wire x2="416" y1="1616" y2="1616" x1="288" />
            <wire x2="432" y1="1616" y2="1616" x1="416" />
            <wire x2="496" y1="1616" y2="1616" x1="432" />
            <wire x2="544" y1="1616" y2="1616" x1="496" />
            <wire x2="544" y1="1616" y2="1648" x1="544" />
            <wire x2="560" y1="1648" y2="1648" x1="544" />
            <wire x2="496" y1="1616" y2="1680" x1="496" />
            <wire x2="1184" y1="1680" y2="1680" x1="496" />
            <wire x2="1184" y1="1168" y2="1168" x1="432" />
            <wire x2="432" y1="1168" y2="1616" x1="432" />
            <wire x2="560" y1="1584" y2="1584" x1="544" />
            <wire x2="544" y1="1584" y2="1616" x1="544" />
        </branch>
        <iomarker fontsize="28" x="288" y="688" name="A" orien="R180" />
        <iomarker fontsize="28" x="288" y="1040" name="B" orien="R180" />
        <iomarker fontsize="28" x="288" y="1344" name="C" orien="R180" />
        <iomarker fontsize="28" x="288" y="1616" name="D" orien="R180" />
        <iomarker fontsize="28" x="2128" y="1184" name="Z" orien="R0" />
    </sheet>
</drawing>