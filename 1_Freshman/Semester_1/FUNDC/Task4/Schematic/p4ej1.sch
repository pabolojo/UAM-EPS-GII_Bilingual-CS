<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="CLR" />
        <signal name="CLK" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="XLXN_11" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="XLXN_16" />
        <signal name="XLXN_17" />
        <signal name="S0" />
        <signal name="XLXN_60" />
        <signal name="XLXN_61" />
        <signal name="XLXN_64" />
        <signal name="XLXN_65" />
        <signal name="S1" />
        <signal name="XLXN_81" />
        <signal name="XLXN_86" />
        <signal name="XLXN_90" />
        <signal name="RD" />
        <signal name="XLXN_95" />
        <signal name="RI" />
        <signal name="VI" />
        <signal name="AI" />
        <signal name="VD" />
        <signal name="AD" />
        <port polarity="Input" name="CLR" />
        <port polarity="Input" name="CLK" />
        <port polarity="Input" name="S0" />
        <port polarity="Input" name="S1" />
        <port polarity="Output" name="RD" />
        <port polarity="Output" name="RI" />
        <port polarity="Output" name="VI" />
        <port polarity="Output" name="AI" />
        <port polarity="Output" name="VD" />
        <port polarity="Output" name="AD" />
        <blockdef name="fdc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <rect width="256" x="64" y="-320" height="256" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
        </blockdef>
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
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <block symbolname="fdc" name="XLXI_2">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="XLXN_6" name="D" />
            <blockpin signalname="XLXN_86" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_3">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="XLXN_8" name="D" />
            <blockpin signalname="XLXN_81" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_4">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="XLXN_7" name="D" />
            <blockpin signalname="RD" name="Q" />
        </block>
        <block symbolname="or3" name="XLXI_5">
            <blockpin signalname="XLXN_11" name="I0" />
            <blockpin signalname="XLXN_10" name="I1" />
            <blockpin signalname="XLXN_9" name="I2" />
            <blockpin signalname="XLXN_6" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_6">
            <blockpin signalname="XLXN_17" name="I0" />
            <blockpin signalname="XLXN_16" name="I1" />
            <blockpin signalname="XLXN_15" name="I2" />
            <blockpin signalname="XLXN_7" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_7">
            <blockpin signalname="XLXN_14" name="I0" />
            <blockpin signalname="XLXN_13" name="I1" />
            <blockpin signalname="XLXN_8" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_8">
            <blockpin signalname="XLXN_95" name="I0" />
            <blockpin signalname="XLXN_81" name="I1" />
            <blockpin signalname="XLXN_10" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_11">
            <blockpin signalname="XLXN_95" name="I0" />
            <blockpin signalname="RD" name="I1" />
            <blockpin signalname="XLXN_16" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_12">
            <blockpin signalname="XLXN_90" name="I0" />
            <blockpin signalname="RD" name="I1" />
            <blockpin signalname="XLXN_17" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_13">
            <blockpin signalname="S1" name="I0" />
            <blockpin signalname="XLXN_95" name="I1" />
            <blockpin signalname="RI" name="I2" />
            <blockpin signalname="XLXN_9" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_14">
            <blockpin signalname="S0" name="I0" />
            <blockpin signalname="XLXN_95" name="I1" />
            <blockpin signalname="RD" name="I2" />
            <blockpin signalname="XLXN_11" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_15">
            <blockpin signalname="XLXN_86" name="I0" />
            <blockpin signalname="XLXN_81" name="I1" />
            <blockpin signalname="RI" name="I2" />
            <blockpin signalname="XLXN_15" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_9">
            <blockpin signalname="XLXN_86" name="I0" />
            <blockpin signalname="XLXN_90" name="I1" />
            <blockpin signalname="XLXN_13" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_10">
            <blockpin signalname="XLXN_95" name="I0" />
            <blockpin signalname="XLXN_81" name="I1" />
            <blockpin signalname="XLXN_14" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_28">
            <blockpin signalname="XLXN_86" name="I" />
            <blockpin signalname="XLXN_95" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_30">
            <blockpin signalname="RD" name="I" />
            <blockpin signalname="RI" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_35">
            <blockpin signalname="XLXN_86" name="I0" />
            <blockpin signalname="XLXN_81" name="I1" />
            <blockpin signalname="RD" name="I2" />
            <blockpin signalname="AI" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_36">
            <blockpin signalname="XLXN_65" name="I0" />
            <blockpin signalname="XLXN_64" name="I1" />
            <blockpin signalname="VD" name="O" />
        </block>
        <block symbolname="and3" name="XLXI_37">
            <blockpin signalname="XLXN_86" name="I0" />
            <blockpin signalname="XLXN_81" name="I1" />
            <blockpin signalname="RI" name="I2" />
            <blockpin signalname="AD" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_38">
            <blockpin signalname="XLXN_95" name="I0" />
            <blockpin signalname="RD" name="I1" />
            <blockpin signalname="XLXN_60" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_39">
            <blockpin signalname="XLXN_90" name="I0" />
            <blockpin signalname="RD" name="I1" />
            <blockpin signalname="XLXN_61" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_47">
            <blockpin signalname="XLXN_90" name="I0" />
            <blockpin signalname="RI" name="I1" />
            <blockpin signalname="XLXN_65" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_48">
            <blockpin signalname="XLXN_61" name="I0" />
            <blockpin signalname="XLXN_60" name="I1" />
            <blockpin signalname="VI" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_46">
            <blockpin signalname="XLXN_95" name="I0" />
            <blockpin signalname="RI" name="I1" />
            <blockpin signalname="XLXN_64" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_51">
            <blockpin signalname="XLXN_81" name="I" />
            <blockpin signalname="XLXN_90" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1552" y="1568" name="XLXI_3" orien="R0" />
        <instance x="1552" y="2016" name="XLXI_4" orien="R0" />
        <instance x="1552" y="1104" name="XLXI_2" orien="R0" />
        <branch name="CLR">
            <wire x2="1488" y1="1984" y2="1984" x1="928" />
            <wire x2="1552" y1="1984" y2="1984" x1="1488" />
            <wire x2="1552" y1="1072" y2="1072" x1="1488" />
            <wire x2="1488" y1="1072" y2="1536" x1="1488" />
            <wire x2="1552" y1="1536" y2="1536" x1="1488" />
            <wire x2="1488" y1="1536" y2="1984" x1="1488" />
        </branch>
        <iomarker fontsize="28" x="928" y="1984" name="CLR" orien="R180" />
        <branch name="CLK">
            <wire x2="1472" y1="2048" y2="2048" x1="928" />
            <wire x2="1552" y1="976" y2="976" x1="1472" />
            <wire x2="1472" y1="976" y2="1440" x1="1472" />
            <wire x2="1552" y1="1440" y2="1440" x1="1472" />
            <wire x2="1472" y1="1440" y2="1888" x1="1472" />
            <wire x2="1552" y1="1888" y2="1888" x1="1472" />
            <wire x2="1472" y1="1888" y2="2048" x1="1472" />
        </branch>
        <iomarker fontsize="28" x="928" y="2048" name="CLK" orien="R180" />
        <branch name="XLXN_6">
            <wire x2="1552" y1="848" y2="848" x1="1520" />
        </branch>
        <instance x="1264" y="976" name="XLXI_5" orien="R0" />
        <branch name="XLXN_7">
            <wire x2="1552" y1="1760" y2="1760" x1="1520" />
        </branch>
        <instance x="1264" y="1888" name="XLXI_6" orien="R0" />
        <branch name="XLXN_8">
            <wire x2="1552" y1="1312" y2="1312" x1="1520" />
        </branch>
        <instance x="1264" y="1408" name="XLXI_7" orien="R0" />
        <instance x="800" y="1856" name="XLXI_11" orien="R0" />
        <instance x="800" y="1984" name="XLXI_12" orien="R0" />
        <instance x="784" y="944" name="XLXI_8" orien="R0" />
        <instance x="784" y="816" name="XLXI_13" orien="R0" />
        <instance x="784" y="1136" name="XLXI_14" orien="R0" />
        <instance x="800" y="1760" name="XLXI_15" orien="R0" />
        <branch name="XLXN_9">
            <wire x2="1264" y1="688" y2="688" x1="1040" />
            <wire x2="1264" y1="688" y2="784" x1="1264" />
        </branch>
        <branch name="XLXN_10">
            <wire x2="1264" y1="848" y2="848" x1="1040" />
        </branch>
        <branch name="XLXN_11">
            <wire x2="1264" y1="1008" y2="1008" x1="1040" />
            <wire x2="1264" y1="912" y2="1008" x1="1264" />
        </branch>
        <branch name="XLXN_13">
            <wire x2="1248" y1="1232" y2="1232" x1="1040" />
            <wire x2="1248" y1="1232" y2="1280" x1="1248" />
            <wire x2="1264" y1="1280" y2="1280" x1="1248" />
        </branch>
        <branch name="XLXN_14">
            <wire x2="1248" y1="1376" y2="1376" x1="1040" />
            <wire x2="1264" y1="1344" y2="1344" x1="1248" />
            <wire x2="1248" y1="1344" y2="1376" x1="1248" />
        </branch>
        <instance x="784" y="1328" name="XLXI_9" orien="R0" />
        <instance x="784" y="1472" name="XLXI_10" orien="R0" />
        <branch name="XLXN_15">
            <wire x2="1264" y1="1632" y2="1632" x1="1056" />
            <wire x2="1264" y1="1632" y2="1696" x1="1264" />
        </branch>
        <branch name="XLXN_16">
            <wire x2="1264" y1="1760" y2="1760" x1="1056" />
        </branch>
        <branch name="XLXN_17">
            <wire x2="1264" y1="1888" y2="1888" x1="1056" />
            <wire x2="1264" y1="1824" y2="1888" x1="1264" />
        </branch>
        <instance x="2016" y="880" name="XLXI_28" orien="R0" />
        <instance x="2016" y="1792" name="XLXI_30" orien="R0" />
        <branch name="S0">
            <wire x2="288" y1="832" y2="832" x1="160" />
            <wire x2="288" y1="832" y2="1072" x1="288" />
            <wire x2="784" y1="1072" y2="1072" x1="288" />
        </branch>
        <iomarker fontsize="28" x="160" y="1760" name="S1" orien="R180" />
        <iomarker fontsize="28" x="160" y="832" name="S0" orien="R180" />
        <instance x="2992" y="928" name="XLXI_35" orien="R0" />
        <instance x="2992" y="1184" name="XLXI_36" orien="R0" />
        <instance x="2992" y="1360" name="XLXI_37" orien="R0" />
        <branch name="XLXN_60">
            <wire x2="2976" y1="576" y2="576" x1="2880" />
            <wire x2="2976" y1="576" y2="608" x1="2976" />
            <wire x2="2992" y1="608" y2="608" x1="2976" />
        </branch>
        <branch name="XLXN_61">
            <wire x2="2976" y1="688" y2="688" x1="2880" />
            <wire x2="2992" y1="672" y2="672" x1="2976" />
            <wire x2="2976" y1="672" y2="688" x1="2976" />
        </branch>
        <instance x="2624" y="784" name="XLXI_39" orien="R0" />
        <branch name="XLXN_64">
            <wire x2="2976" y1="1024" y2="1024" x1="2880" />
            <wire x2="2976" y1="1024" y2="1056" x1="2976" />
            <wire x2="2992" y1="1056" y2="1056" x1="2976" />
        </branch>
        <branch name="XLXN_65">
            <wire x2="2976" y1="1136" y2="1136" x1="2880" />
            <wire x2="2992" y1="1120" y2="1120" x1="2976" />
            <wire x2="2976" y1="1120" y2="1136" x1="2976" />
        </branch>
        <instance x="2624" y="1232" name="XLXI_47" orien="R0" />
        <instance x="2992" y="736" name="XLXI_48" orien="R0" />
        <instance x="2624" y="672" name="XLXI_38" orien="R0" />
        <instance x="2624" y="1120" name="XLXI_46" orien="R0" />
        <instance x="2016" y="1344" name="XLXI_51" orien="R0" />
        <branch name="S1">
            <wire x2="464" y1="1760" y2="1760" x1="160" />
            <wire x2="784" y1="752" y2="752" x1="464" />
            <wire x2="464" y1="752" y2="1760" x1="464" />
        </branch>
        <branch name="XLXN_81">
            <wire x2="784" y1="816" y2="816" x1="720" />
            <wire x2="720" y1="816" y2="1152" x1="720" />
            <wire x2="1984" y1="1152" y2="1152" x1="720" />
            <wire x2="1984" y1="1152" y2="1312" x1="1984" />
            <wire x2="2016" y1="1312" y2="1312" x1="1984" />
            <wire x2="2464" y1="1152" y2="1152" x1="1984" />
            <wire x2="2464" y1="1152" y2="1232" x1="2464" />
            <wire x2="2992" y1="1232" y2="1232" x1="2464" />
            <wire x2="720" y1="1152" y2="1344" x1="720" />
            <wire x2="784" y1="1344" y2="1344" x1="720" />
            <wire x2="720" y1="1344" y2="1632" x1="720" />
            <wire x2="800" y1="1632" y2="1632" x1="720" />
            <wire x2="1984" y1="1312" y2="1312" x1="1936" />
            <wire x2="2464" y1="800" y2="1152" x1="2464" />
            <wire x2="2992" y1="800" y2="800" x1="2464" />
        </branch>
        <branch name="XLXN_86">
            <wire x2="768" y1="1088" y2="1264" x1="768" />
            <wire x2="784" y1="1264" y2="1264" x1="768" />
            <wire x2="768" y1="1264" y2="1696" x1="768" />
            <wire x2="800" y1="1696" y2="1696" x1="768" />
            <wire x2="1984" y1="1088" y2="1088" x1="768" />
            <wire x2="2480" y1="1088" y2="1088" x1="1984" />
            <wire x2="2480" y1="1088" y2="1296" x1="2480" />
            <wire x2="2992" y1="1296" y2="1296" x1="2480" />
            <wire x2="1984" y1="848" y2="848" x1="1936" />
            <wire x2="2016" y1="848" y2="848" x1="1984" />
            <wire x2="1984" y1="848" y2="1088" x1="1984" />
            <wire x2="2480" y1="864" y2="1088" x1="2480" />
            <wire x2="2992" y1="864" y2="864" x1="2480" />
        </branch>
        <branch name="XLXN_90">
            <wire x2="736" y1="1120" y2="1200" x1="736" />
            <wire x2="784" y1="1200" y2="1200" x1="736" />
            <wire x2="736" y1="1200" y2="1920" x1="736" />
            <wire x2="800" y1="1920" y2="1920" x1="736" />
            <wire x2="2288" y1="1120" y2="1120" x1="736" />
            <wire x2="2288" y1="1120" y2="1312" x1="2288" />
            <wire x2="2448" y1="1120" y2="1120" x1="2288" />
            <wire x2="2448" y1="1120" y2="1168" x1="2448" />
            <wire x2="2624" y1="1168" y2="1168" x1="2448" />
            <wire x2="2288" y1="1312" y2="1312" x1="2240" />
            <wire x2="2448" y1="720" y2="1120" x1="2448" />
            <wire x2="2624" y1="720" y2="720" x1="2448" />
        </branch>
        <branch name="RD">
            <wire x2="768" y1="800" y2="800" x1="576" />
            <wire x2="768" y1="800" y2="944" x1="768" />
            <wire x2="784" y1="944" y2="944" x1="768" />
            <wire x2="576" y1="800" y2="1728" x1="576" />
            <wire x2="784" y1="1728" y2="1728" x1="576" />
            <wire x2="800" y1="1728" y2="1728" x1="784" />
            <wire x2="784" y1="1728" y2="1856" x1="784" />
            <wire x2="784" y1="1856" y2="2144" x1="784" />
            <wire x2="1984" y1="2144" y2="2144" x1="784" />
            <wire x2="2320" y1="2144" y2="2144" x1="1984" />
            <wire x2="2800" y1="2144" y2="2144" x1="2320" />
            <wire x2="800" y1="1856" y2="1856" x1="784" />
            <wire x2="1984" y1="1760" y2="1760" x1="1936" />
            <wire x2="2016" y1="1760" y2="1760" x1="1984" />
            <wire x2="1984" y1="1760" y2="2144" x1="1984" />
            <wire x2="2624" y1="544" y2="544" x1="2320" />
            <wire x2="2320" y1="544" y2="656" x1="2320" />
            <wire x2="2624" y1="656" y2="656" x1="2320" />
            <wire x2="2320" y1="656" y2="752" x1="2320" />
            <wire x2="2320" y1="752" y2="2144" x1="2320" />
            <wire x2="2944" y1="752" y2="752" x1="2320" />
            <wire x2="2800" y1="1344" y2="2144" x1="2800" />
            <wire x2="3280" y1="1344" y2="1344" x1="2800" />
            <wire x2="2944" y1="736" y2="752" x1="2944" />
            <wire x2="2992" y1="736" y2="736" x1="2944" />
        </branch>
        <branch name="XLXN_95">
            <wire x2="784" y1="688" y2="688" x1="704" />
            <wire x2="704" y1="688" y2="768" x1="704" />
            <wire x2="2288" y1="768" y2="768" x1="704" />
            <wire x2="2288" y1="768" y2="848" x1="2288" />
            <wire x2="2288" y1="848" y2="1056" x1="2288" />
            <wire x2="2624" y1="1056" y2="1056" x1="2288" />
            <wire x2="704" y1="768" y2="880" x1="704" />
            <wire x2="784" y1="880" y2="880" x1="704" />
            <wire x2="704" y1="880" y2="1008" x1="704" />
            <wire x2="784" y1="1008" y2="1008" x1="704" />
            <wire x2="704" y1="1008" y2="1408" x1="704" />
            <wire x2="784" y1="1408" y2="1408" x1="704" />
            <wire x2="704" y1="1408" y2="1792" x1="704" />
            <wire x2="800" y1="1792" y2="1792" x1="704" />
            <wire x2="2288" y1="848" y2="848" x1="2240" />
            <wire x2="2624" y1="608" y2="608" x1="2288" />
            <wire x2="2288" y1="608" y2="768" x1="2288" />
        </branch>
        <branch name="VI">
            <wire x2="3280" y1="640" y2="640" x1="3248" />
        </branch>
        <iomarker fontsize="28" x="3280" y="640" name="VI" orien="R0" />
        <branch name="AI">
            <wire x2="3280" y1="800" y2="800" x1="3248" />
        </branch>
        <iomarker fontsize="28" x="3280" y="800" name="AI" orien="R0" />
        <branch name="VD">
            <wire x2="3280" y1="1088" y2="1088" x1="3248" />
        </branch>
        <iomarker fontsize="28" x="3280" y="1088" name="VD" orien="R0" />
        <branch name="AD">
            <wire x2="3280" y1="1232" y2="1232" x1="3248" />
        </branch>
        <iomarker fontsize="28" x="3280" y="1232" name="AD" orien="R0" />
        <iomarker fontsize="28" x="3280" y="944" name="RI" orien="R0" />
        <branch name="RI">
            <wire x2="784" y1="544" y2="544" x1="752" />
            <wire x2="784" y1="544" y2="624" x1="784" />
            <wire x2="2304" y1="544" y2="544" x1="784" />
            <wire x2="2304" y1="544" y2="1760" x1="2304" />
            <wire x2="2432" y1="1760" y2="1760" x1="2304" />
            <wire x2="752" y1="544" y2="1488" x1="752" />
            <wire x2="800" y1="1488" y2="1488" x1="752" />
            <wire x2="800" y1="1488" y2="1568" x1="800" />
            <wire x2="2304" y1="1760" y2="1760" x1="2240" />
            <wire x2="2432" y1="1168" y2="1168" x1="2400" />
            <wire x2="2432" y1="1168" y2="1760" x1="2432" />
            <wire x2="2400" y1="1168" y2="1200" x1="2400" />
            <wire x2="2944" y1="1200" y2="1200" x1="2400" />
            <wire x2="3280" y1="944" y2="944" x1="2432" />
            <wire x2="2432" y1="944" y2="992" x1="2432" />
            <wire x2="2624" y1="992" y2="992" x1="2432" />
            <wire x2="2432" y1="992" y2="1104" x1="2432" />
            <wire x2="2624" y1="1104" y2="1104" x1="2432" />
            <wire x2="2432" y1="1104" y2="1168" x1="2432" />
            <wire x2="2944" y1="1168" y2="1200" x1="2944" />
            <wire x2="2992" y1="1168" y2="1168" x1="2944" />
        </branch>
        <iomarker fontsize="28" x="3280" y="1344" name="RD" orien="R0" />
    </sheet>
</drawing>