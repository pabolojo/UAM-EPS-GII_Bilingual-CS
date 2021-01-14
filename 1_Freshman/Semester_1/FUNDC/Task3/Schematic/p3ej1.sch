<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="Q0" />
        <signal name="Q2" />
        <signal name="CLR" />
        <signal name="Q3" />
        <signal name="XLXN_53" />
        <signal name="CLK" />
        <signal name="Q1" />
        <signal name="XLXN_89" />
        <signal name="XLXN_93" />
        <signal name="XLXN_94" />
        <port polarity="Output" name="Q0" />
        <port polarity="Output" name="Q2" />
        <port polarity="Input" name="CLR" />
        <port polarity="Output" name="Q3" />
        <port polarity="Input" name="CLK" />
        <port polarity="Output" name="Q1" />
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
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
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
        <block symbolname="fdc" name="XLXI_1">
            <attr value="FDC" name="VeriModel" />
            <attr value="FDC" name="VhdlModel" />
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_89" name="CLR" />
            <blockpin signalname="XLXN_53" name="D" />
            <blockpin signalname="Q0" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_2">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_89" name="CLR" />
            <blockpin signalname="Q0" name="D" />
            <blockpin signalname="Q1" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_3">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_89" name="CLR" />
            <blockpin signalname="Q1" name="D" />
            <blockpin signalname="Q2" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_4">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_89" name="CLR" />
            <blockpin signalname="Q2" name="D" />
            <blockpin signalname="Q3" name="Q" />
        </block>
        <block symbolname="and2" name="XLXI_17">
            <blockpin signalname="XLXN_94" name="I0" />
            <blockpin signalname="Q3" name="I1" />
            <blockpin signalname="XLXN_93" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_20">
            <blockpin signalname="Q3" name="I" />
            <blockpin signalname="XLXN_53" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_35">
            <blockpin signalname="Q0" name="I" />
            <blockpin signalname="XLXN_94" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_37">
            <blockpin signalname="XLXN_93" name="I0" />
            <blockpin signalname="CLR" name="I1" />
            <blockpin signalname="XLXN_89" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="720" y="1136" name="XLXI_1" orien="R0" />
        <instance x="1216" y="1136" name="XLXI_2" orien="R0" />
        <instance x="1744" y="1136" name="XLXI_3" orien="R0" />
        <instance x="2240" y="1136" name="XLXI_4" orien="R0" />
        <branch name="Q0">
            <wire x2="1152" y1="880" y2="880" x1="1104" />
            <wire x2="1216" y1="880" y2="880" x1="1152" />
            <wire x2="1152" y1="672" y2="704" x1="1152" />
            <wire x2="2864" y1="704" y2="704" x1="1152" />
            <wire x2="2864" y1="704" y2="912" x1="2864" />
            <wire x2="1152" y1="704" y2="880" x1="1152" />
            <wire x2="2864" y1="912" y2="912" x1="2640" />
            <wire x2="2640" y1="912" y2="944" x1="2640" />
        </branch>
        <branch name="Q2">
            <wire x2="2176" y1="880" y2="880" x1="2128" />
            <wire x2="2240" y1="880" y2="880" x1="2176" />
            <wire x2="2176" y1="672" y2="880" x1="2176" />
        </branch>
        <iomarker fontsize="28" x="352" y="1008" name="CLK" orien="R180" />
        <iomarker fontsize="28" x="1152" y="672" name="Q0" orien="R270" />
        <iomarker fontsize="28" x="1664" y="672" name="Q1" orien="R270" />
        <iomarker fontsize="28" x="2176" y="672" name="Q2" orien="R270" />
        <iomarker fontsize="28" x="2640" y="656" name="Q3" orien="R270" />
        <branch name="Q3">
            <wire x2="384" y1="736" y2="880" x1="384" />
            <wire x2="464" y1="880" y2="880" x1="384" />
            <wire x2="2752" y1="736" y2="736" x1="384" />
            <wire x2="2752" y1="736" y2="880" x1="2752" />
            <wire x2="2896" y1="880" y2="880" x1="2752" />
            <wire x2="2640" y1="880" y2="880" x1="2624" />
            <wire x2="2752" y1="880" y2="880" x1="2640" />
            <wire x2="2640" y1="656" y2="880" x1="2640" />
        </branch>
        <branch name="XLXN_53">
            <wire x2="720" y1="880" y2="880" x1="688" />
        </branch>
        <instance x="464" y="912" name="XLXI_20" orien="R0" />
        <branch name="CLK">
            <wire x2="400" y1="1008" y2="1008" x1="352" />
            <wire x2="400" y1="1008" y2="1232" x1="400" />
            <wire x2="400" y1="1232" y2="1328" x1="400" />
            <wire x2="704" y1="1328" y2="1328" x1="400" />
            <wire x2="720" y1="1008" y2="1008" x1="704" />
            <wire x2="704" y1="1008" y2="1168" x1="704" />
            <wire x2="1184" y1="1168" y2="1168" x1="704" />
            <wire x2="1680" y1="1168" y2="1168" x1="1184" />
            <wire x2="2192" y1="1168" y2="1168" x1="1680" />
            <wire x2="704" y1="1168" y2="1328" x1="704" />
            <wire x2="1216" y1="1008" y2="1008" x1="1184" />
            <wire x2="1184" y1="1008" y2="1168" x1="1184" />
            <wire x2="1744" y1="1008" y2="1008" x1="1680" />
            <wire x2="1680" y1="1008" y2="1168" x1="1680" />
            <wire x2="2192" y1="1008" y2="1168" x1="2192" />
            <wire x2="2240" y1="1008" y2="1008" x1="2192" />
        </branch>
        <instance x="2896" y="1008" name="XLXI_17" orien="R0" />
        <instance x="2640" y="976" name="XLXI_35" orien="R0" />
        <branch name="Q1">
            <wire x2="1664" y1="880" y2="880" x1="1600" />
            <wire x2="1744" y1="880" y2="880" x1="1664" />
            <wire x2="1664" y1="672" y2="880" x1="1664" />
        </branch>
        <instance x="432" y="1280" name="XLXI_37" orien="R0" />
        <branch name="CLR">
            <wire x2="432" y1="1152" y2="1152" x1="352" />
        </branch>
        <iomarker fontsize="28" x="352" y="1152" name="CLR" orien="R180" />
        <branch name="XLXN_89">
            <wire x2="720" y1="1184" y2="1184" x1="688" />
            <wire x2="1216" y1="1184" y2="1184" x1="720" />
            <wire x2="1744" y1="1184" y2="1184" x1="1216" />
            <wire x2="2240" y1="1184" y2="1184" x1="1744" />
            <wire x2="720" y1="1104" y2="1184" x1="720" />
            <wire x2="1216" y1="1104" y2="1184" x1="1216" />
            <wire x2="1744" y1="1104" y2="1184" x1="1744" />
            <wire x2="2240" y1="1104" y2="1184" x1="2240" />
        </branch>
        <branch name="XLXN_93">
            <wire x2="368" y1="1120" y2="1216" x1="368" />
            <wire x2="432" y1="1216" y2="1216" x1="368" />
            <wire x2="3232" y1="1120" y2="1120" x1="368" />
            <wire x2="3232" y1="912" y2="912" x1="3152" />
            <wire x2="3232" y1="912" y2="1120" x1="3232" />
        </branch>
        <branch name="XLXN_94">
            <wire x2="2896" y1="944" y2="944" x1="2864" />
        </branch>
    </sheet>
</drawing>