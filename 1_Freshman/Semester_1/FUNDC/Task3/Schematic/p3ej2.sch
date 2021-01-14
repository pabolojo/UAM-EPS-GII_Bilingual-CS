<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="CLK" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_10" />
        <signal name="XLXN_11" />
        <signal name="Q0" />
        <signal name="Q1" />
        <signal name="Q2" />
        <signal name="Q3" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="XLXN_16" />
        <signal name="XLXN_17" />
        <signal name="XLXN_19" />
        <signal name="XLXN_21" />
        <signal name="XLXN_25" />
        <signal name="INIT" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_29" />
        <signal name="XLXN_30" />
        <signal name="XLXN_31" />
        <signal name="XLXN_32" />
        <signal name="XLXN_33" />
        <port polarity="Input" name="CLK" />
        <port polarity="Output" name="Q0" />
        <port polarity="Output" name="Q1" />
        <port polarity="Output" name="Q2" />
        <port polarity="Output" name="Q3" />
        <port polarity="Input" name="INIT" />
        <blockdef name="cb4cled">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="256" x="64" y="-704" height="640" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <line x2="320" y1="-448" y2="-448" x1="384" />
            <line x2="320" y1="-512" y2="-512" x1="384" />
            <line x2="320" y1="-576" y2="-576" x1="384" />
            <line x2="320" y1="-640" y2="-640" x1="384" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <line x2="64" y1="-640" y2="-640" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <blockdef name="gnd">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-96" x1="64" />
            <line x2="52" y1="-48" y2="-48" x1="76" />
            <line x2="60" y1="-32" y2="-32" x1="68" />
            <line x2="40" y1="-64" y2="-64" x1="88" />
            <line x2="64" y1="-64" y2="-80" x1="64" />
            <line x2="64" y1="-128" y2="-96" x1="64" />
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
        <block symbolname="cb4cled" name="XLXI_1">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_17" name="CE" />
            <blockpin signalname="INIT" name="CLR" />
            <blockpin signalname="XLXN_6" name="D0" />
            <blockpin signalname="XLXN_10" name="D1" />
            <blockpin signalname="XLXN_7" name="D2" />
            <blockpin signalname="XLXN_11" name="D3" />
            <blockpin signalname="XLXN_33" name="L" />
            <blockpin signalname="XLXN_17" name="UP" />
            <blockpin name="CEO" />
            <blockpin signalname="Q0" name="Q0" />
            <blockpin signalname="Q1" name="Q1" />
            <blockpin signalname="Q2" name="Q2" />
            <blockpin signalname="Q3" name="Q3" />
            <blockpin name="TC" />
        </block>
        <block symbolname="vcc" name="XLXI_2">
            <blockpin signalname="XLXN_17" name="P" />
        </block>
        <block symbolname="vcc" name="XLXI_4">
            <blockpin signalname="XLXN_6" name="P" />
        </block>
        <block symbolname="vcc" name="XLXI_5">
            <blockpin signalname="XLXN_7" name="P" />
        </block>
        <block symbolname="gnd" name="XLXI_6">
            <blockpin signalname="XLXN_11" name="G" />
        </block>
        <block symbolname="gnd" name="XLXI_7">
            <blockpin signalname="XLXN_10" name="G" />
        </block>
        <block symbolname="and4" name="XLXI_8">
            <blockpin signalname="Q3" name="I0" />
            <blockpin signalname="Q2" name="I1" />
            <blockpin signalname="Q1" name="I2" />
            <blockpin signalname="Q0" name="I3" />
            <blockpin signalname="XLXN_32" name="O" />
        </block>
        <block symbolname="and4" name="XLXI_9">
            <blockpin signalname="XLXN_28" name="I0" />
            <blockpin signalname="XLXN_29" name="I1" />
            <blockpin signalname="XLXN_30" name="I2" />
            <blockpin signalname="XLXN_27" name="I3" />
            <blockpin signalname="XLXN_31" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_10">
            <blockpin signalname="Q0" name="I" />
            <blockpin signalname="XLXN_27" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_11">
            <blockpin signalname="Q3" name="I" />
            <blockpin signalname="XLXN_28" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_12">
            <blockpin signalname="Q2" name="I" />
            <blockpin signalname="XLXN_29" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_13">
            <blockpin signalname="Q1" name="I" />
            <blockpin signalname="XLXN_30" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_14">
            <blockpin signalname="XLXN_32" name="I0" />
            <blockpin signalname="XLXN_31" name="I1" />
            <blockpin signalname="XLXN_33" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1456" y="1488" name="XLXI_1" orien="R0" />
        <branch name="CLK">
            <wire x2="1456" y1="1360" y2="1360" x1="1216" />
        </branch>
        <iomarker fontsize="28" x="1216" y="1360" name="CLK" orien="R180" />
        <iomarker fontsize="28" x="1216" y="1456" name="INIT" orien="R180" />
        <instance x="1152" y="1296" name="XLXI_2" orien="R0" />
        <instance x="1296" y="832" name="XLXI_4" orien="R0" />
        <instance x="1296" y="960" name="XLXI_5" orien="R0" />
        <branch name="XLXN_6">
            <wire x2="1360" y1="832" y2="848" x1="1360" />
            <wire x2="1456" y1="848" y2="848" x1="1360" />
        </branch>
        <branch name="XLXN_7">
            <wire x2="1360" y1="960" y2="976" x1="1360" />
            <wire x2="1456" y1="976" y2="976" x1="1360" />
        </branch>
        <instance x="1216" y="1168" name="XLXI_6" orien="R0" />
        <instance x="1216" y="1040" name="XLXI_7" orien="R0" />
        <branch name="XLXN_10">
            <wire x2="1280" y1="864" y2="912" x1="1280" />
            <wire x2="1440" y1="864" y2="864" x1="1280" />
            <wire x2="1440" y1="864" y2="912" x1="1440" />
            <wire x2="1456" y1="912" y2="912" x1="1440" />
        </branch>
        <branch name="XLXN_11">
            <wire x2="1280" y1="1024" y2="1040" x1="1280" />
            <wire x2="1360" y1="1024" y2="1024" x1="1280" />
            <wire x2="1360" y1="1024" y2="1040" x1="1360" />
            <wire x2="1456" y1="1040" y2="1040" x1="1360" />
        </branch>
        <branch name="Q0">
            <wire x2="1856" y1="848" y2="848" x1="1840" />
            <wire x2="1952" y1="848" y2="848" x1="1856" />
            <wire x2="1952" y1="848" y2="1184" x1="1952" />
            <wire x2="2112" y1="1184" y2="1184" x1="1952" />
            <wire x2="2000" y1="848" y2="848" x1="1952" />
            <wire x2="1952" y1="832" y2="848" x1="1952" />
            <wire x2="2320" y1="832" y2="832" x1="1952" />
            <wire x2="2320" y1="832" y2="848" x1="2320" />
            <wire x2="2432" y1="848" y2="848" x1="2320" />
        </branch>
        <branch name="Q1">
            <wire x2="1856" y1="912" y2="912" x1="1840" />
            <wire x2="1968" y1="912" y2="912" x1="1856" />
            <wire x2="1968" y1="912" y2="1232" x1="1968" />
            <wire x2="2112" y1="1232" y2="1232" x1="1968" />
            <wire x2="2000" y1="912" y2="912" x1="1968" />
            <wire x2="1968" y1="816" y2="912" x1="1968" />
            <wire x2="2304" y1="816" y2="816" x1="1968" />
            <wire x2="2304" y1="816" y2="912" x1="2304" />
            <wire x2="2432" y1="912" y2="912" x1="2304" />
        </branch>
        <branch name="Q2">
            <wire x2="1856" y1="976" y2="976" x1="1840" />
            <wire x2="1984" y1="976" y2="976" x1="1856" />
            <wire x2="1984" y1="976" y2="1280" x1="1984" />
            <wire x2="2112" y1="1280" y2="1280" x1="1984" />
            <wire x2="2000" y1="976" y2="976" x1="1984" />
            <wire x2="1984" y1="784" y2="976" x1="1984" />
            <wire x2="2288" y1="784" y2="784" x1="1984" />
            <wire x2="2288" y1="784" y2="976" x1="2288" />
            <wire x2="2432" y1="976" y2="976" x1="2288" />
        </branch>
        <branch name="Q3">
            <wire x2="1856" y1="1040" y2="1040" x1="1840" />
            <wire x2="2000" y1="1040" y2="1040" x1="1856" />
            <wire x2="1856" y1="1040" y2="1056" x1="1856" />
            <wire x2="1856" y1="1056" y2="1328" x1="1856" />
            <wire x2="2112" y1="1328" y2="1328" x1="1856" />
            <wire x2="2320" y1="1056" y2="1056" x1="1856" />
            <wire x2="2320" y1="1040" y2="1056" x1="2320" />
            <wire x2="2432" y1="1040" y2="1040" x1="2320" />
        </branch>
        <instance x="2000" y="1104" name="XLXI_8" orien="R0" />
        <iomarker fontsize="28" x="2112" y="1328" name="Q3" orien="R0" />
        <iomarker fontsize="28" x="2112" y="1280" name="Q2" orien="R0" />
        <iomarker fontsize="28" x="2112" y="1232" name="Q1" orien="R0" />
        <iomarker fontsize="28" x="2112" y="1184" name="Q0" orien="R0" />
        <branch name="XLXN_17">
            <wire x2="1216" y1="1296" y2="1312" x1="1216" />
            <wire x2="1312" y1="1312" y2="1312" x1="1216" />
            <wire x2="1456" y1="1168" y2="1168" x1="1312" />
            <wire x2="1312" y1="1168" y2="1296" x1="1312" />
            <wire x2="1312" y1="1296" y2="1312" x1="1312" />
            <wire x2="1456" y1="1296" y2="1296" x1="1312" />
        </branch>
        <branch name="INIT">
            <wire x2="1456" y1="1456" y2="1456" x1="1216" />
        </branch>
        <instance x="2688" y="1104" name="XLXI_9" orien="R0" />
        <branch name="XLXN_27">
            <wire x2="2688" y1="848" y2="848" x1="2656" />
        </branch>
        <instance x="2432" y="880" name="XLXI_10" orien="R0" />
        <branch name="XLXN_28">
            <wire x2="2688" y1="1040" y2="1040" x1="2656" />
        </branch>
        <instance x="2432" y="1072" name="XLXI_11" orien="R0" />
        <branch name="XLXN_29">
            <wire x2="2688" y1="976" y2="976" x1="2656" />
        </branch>
        <instance x="2432" y="1008" name="XLXI_12" orien="R0" />
        <branch name="XLXN_30">
            <wire x2="2688" y1="912" y2="912" x1="2656" />
        </branch>
        <instance x="2432" y="944" name="XLXI_13" orien="R0" />
        <branch name="XLXN_31">
            <wire x2="2976" y1="944" y2="944" x1="2944" />
        </branch>
        <instance x="2976" y="1072" name="XLXI_14" orien="R0" />
        <branch name="XLXN_32">
            <wire x2="2304" y1="944" y2="944" x1="2256" />
            <wire x2="2304" y1="944" y2="1120" x1="2304" />
            <wire x2="2960" y1="1120" y2="1120" x1="2304" />
            <wire x2="2960" y1="1008" y2="1120" x1="2960" />
            <wire x2="2976" y1="1008" y2="1008" x1="2960" />
        </branch>
        <branch name="XLXN_33">
            <wire x2="1456" y1="1232" y2="1232" x1="1392" />
            <wire x2="1392" y1="1232" y2="1520" x1="1392" />
            <wire x2="3280" y1="1520" y2="1520" x1="1392" />
            <wire x2="3280" y1="976" y2="976" x1="3232" />
            <wire x2="3280" y1="976" y2="1520" x1="3280" />
        </branch>
    </sheet>
</drawing>