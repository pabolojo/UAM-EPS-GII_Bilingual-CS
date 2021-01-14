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
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_9" />
        <signal name="XLXN_10" />
        <signal name="XLXN_11" />
        <signal name="B" />
        <signal name="XLXN_13" />
        <signal name="C" />
        <signal name="A" />
        <signal name="Z" />
        <signal name="XLXN_17" />
        <signal name="XLXN_18" />
        <signal name="XLXN_19" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="A" />
        <port polarity="Output" name="Z" />
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
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <block symbolname="nor2" name="XLXI_1">
            <blockpin signalname="A" name="I0" />
            <blockpin signalname="A" name="I1" />
            <blockpin signalname="XLXN_9" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_2">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="XLXN_10" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_3">
            <blockpin signalname="XLXN_10" name="I0" />
            <blockpin signalname="XLXN_9" name="I1" />
            <blockpin signalname="XLXN_18" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_4">
            <blockpin signalname="C" name="I0" />
            <blockpin signalname="XLXN_11" name="I1" />
            <blockpin signalname="XLXN_7" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_8">
            <blockpin signalname="B" name="I" />
            <blockpin signalname="XLXN_11" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_9">
            <blockpin signalname="XLXN_7" name="I" />
            <blockpin signalname="XLXN_6" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_5">
            <blockpin signalname="XLXN_19" name="I0" />
            <blockpin signalname="XLXN_19" name="I1" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_6">
            <blockpin signalname="XLXN_6" name="I0" />
            <blockpin signalname="XLXN_6" name="I1" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_7">
            <blockpin signalname="XLXN_2" name="I0" />
            <blockpin signalname="XLXN_3" name="I1" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_14">
            <blockpin signalname="XLXN_18" name="I" />
            <blockpin signalname="XLXN_19" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1568" y="1040" name="XLXI_1" orien="R0" />
        <instance x="1568" y="1296" name="XLXI_2" orien="R0" />
        <instance x="2064" y="1168" name="XLXI_3" orien="R0" />
        <instance x="1648" y="2048" name="XLXI_4" orien="R0" />
        <instance x="976" y="1504" name="XLXI_8" orien="R0" />
        <instance x="2016" y="1968" name="XLXI_9" orien="R0" />
        <instance x="2416" y="1424" name="XLXI_5" orien="R0" />
        <instance x="2416" y="1728" name="XLXI_6" orien="R0" />
        <instance x="2752" y="1600" name="XLXI_7" orien="R0" />
        <branch name="XLXN_2">
            <wire x2="2704" y1="1632" y2="1632" x1="2672" />
            <wire x2="2704" y1="1536" y2="1632" x1="2704" />
            <wire x2="2752" y1="1536" y2="1536" x1="2704" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="2704" y1="1328" y2="1328" x1="2672" />
            <wire x2="2704" y1="1328" y2="1472" x1="2704" />
            <wire x2="2752" y1="1472" y2="1472" x1="2704" />
        </branch>
        <branch name="XLXN_6">
            <wire x2="2320" y1="1936" y2="1936" x1="2240" />
            <wire x2="2320" y1="1632" y2="1936" x1="2320" />
            <wire x2="2400" y1="1632" y2="1632" x1="2320" />
            <wire x2="2400" y1="1632" y2="1664" x1="2400" />
            <wire x2="2416" y1="1664" y2="1664" x1="2400" />
            <wire x2="2416" y1="1600" y2="1600" x1="2400" />
            <wire x2="2400" y1="1600" y2="1632" x1="2400" />
        </branch>
        <branch name="XLXN_7">
            <wire x2="1952" y1="1952" y2="1952" x1="1904" />
            <wire x2="1952" y1="1936" y2="1952" x1="1952" />
            <wire x2="2016" y1="1936" y2="1936" x1="1952" />
        </branch>
        <branch name="XLXN_9">
            <wire x2="1936" y1="944" y2="944" x1="1824" />
            <wire x2="1936" y1="944" y2="1040" x1="1936" />
            <wire x2="2064" y1="1040" y2="1040" x1="1936" />
        </branch>
        <branch name="XLXN_10">
            <wire x2="1936" y1="1200" y2="1200" x1="1824" />
            <wire x2="1936" y1="1104" y2="1200" x1="1936" />
            <wire x2="2064" y1="1104" y2="1104" x1="1936" />
        </branch>
        <branch name="XLXN_11">
            <wire x2="1424" y1="1472" y2="1472" x1="1200" />
            <wire x2="1424" y1="1472" y2="1920" x1="1424" />
            <wire x2="1648" y1="1920" y2="1920" x1="1424" />
        </branch>
        <branch name="B">
            <wire x2="976" y1="1200" y2="1200" x1="656" />
            <wire x2="1552" y1="1200" y2="1200" x1="976" />
            <wire x2="1552" y1="1200" y2="1232" x1="1552" />
            <wire x2="1568" y1="1232" y2="1232" x1="1552" />
            <wire x2="976" y1="1200" y2="1216" x1="976" />
            <wire x2="976" y1="1216" y2="1216" x1="896" />
            <wire x2="896" y1="1216" y2="1472" x1="896" />
            <wire x2="976" y1="1472" y2="1472" x1="896" />
            <wire x2="1568" y1="1168" y2="1168" x1="1552" />
            <wire x2="1552" y1="1168" y2="1200" x1="1552" />
        </branch>
        <branch name="C">
            <wire x2="1648" y1="1984" y2="1984" x1="640" />
        </branch>
        <branch name="A">
            <wire x2="736" y1="784" y2="784" x1="656" />
            <wire x2="656" y1="784" y2="944" x1="656" />
            <wire x2="1552" y1="944" y2="944" x1="656" />
            <wire x2="1552" y1="944" y2="976" x1="1552" />
            <wire x2="1568" y1="976" y2="976" x1="1552" />
            <wire x2="1568" y1="912" y2="912" x1="1552" />
            <wire x2="1552" y1="912" y2="944" x1="1552" />
        </branch>
        <iomarker fontsize="28" x="736" y="784" name="A" orien="R0" />
        <iomarker fontsize="28" x="656" y="1200" name="B" orien="R180" />
        <iomarker fontsize="28" x="640" y="1984" name="C" orien="R180" />
        <branch name="Z">
            <wire x2="3072" y1="1504" y2="1504" x1="3008" />
            <wire x2="3296" y1="1504" y2="1504" x1="3072" />
            <wire x2="3328" y1="1504" y2="1504" x1="3296" />
        </branch>
        <iomarker fontsize="28" x="3328" y="1504" name="Z" orien="R0" />
        <instance x="2464" y="1120" name="XLXI_14" orien="R0" />
        <branch name="XLXN_18">
            <wire x2="2384" y1="1072" y2="1072" x1="2320" />
            <wire x2="2384" y1="1072" y2="1088" x1="2384" />
            <wire x2="2464" y1="1088" y2="1088" x1="2384" />
        </branch>
        <branch name="XLXN_19">
            <wire x2="2352" y1="1216" y2="1296" x1="2352" />
            <wire x2="2368" y1="1296" y2="1296" x1="2352" />
            <wire x2="2416" y1="1296" y2="1296" x1="2368" />
            <wire x2="2368" y1="1296" y2="1360" x1="2368" />
            <wire x2="2416" y1="1360" y2="1360" x1="2368" />
            <wire x2="2768" y1="1216" y2="1216" x1="2352" />
            <wire x2="2768" y1="1088" y2="1088" x1="2688" />
            <wire x2="2768" y1="1088" y2="1216" x1="2768" />
        </branch>
    </sheet>
</drawing>