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
        <signal name="Z" />
        <signal name="A" />
        <signal name="B" />
        <signal name="C" />
        <signal name="D" />
        <signal name="XLXN_10" />
        <signal name="XLXN_12" />
        <signal name="XLXN_14" />
        <signal name="XLXN_16" />
        <signal name="XLXN_18" />
        <signal name="XLXN_19" />
        <port polarity="Output" name="Z" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Input" name="D" />
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
        <block symbolname="and2" name="XLXI_1">
            <blockpin signalname="XLXN_12" name="I0" />
            <blockpin signalname="XLXN_10" name="I1" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_5">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_10" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_6">
            <blockpin signalname="B" name="I" />
            <blockpin signalname="XLXN_12" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_7">
            <blockpin signalname="C" name="I" />
            <blockpin signalname="XLXN_14" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_8">
            <blockpin signalname="D" name="I" />
            <blockpin signalname="XLXN_18" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_9">
            <blockpin signalname="B" name="I0" />
            <blockpin signalname="XLXN_14" name="I1" />
            <blockpin signalname="XLXN_16" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_10">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="XLXN_16" name="I1" />
            <blockpin signalname="XLXN_2" name="O" />
        </block>
        <block symbolname="and4" name="XLXI_11">
            <blockpin signalname="XLXN_18" name="I0" />
            <blockpin signalname="XLXN_18" name="I1" />
            <blockpin signalname="XLXN_14" name="I2" />
            <blockpin signalname="XLXN_12" name="I3" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_12">
            <blockpin signalname="XLXN_2" name="I0" />
            <blockpin signalname="XLXN_1" name="I1" />
            <blockpin signalname="XLXN_19" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_13">
            <blockpin signalname="XLXN_3" name="I0" />
            <blockpin signalname="XLXN_19" name="I1" />
            <blockpin signalname="Z" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="960" y="688" name="XLXI_1" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="1632" y1="592" y2="592" x1="1216" />
            <wire x2="1632" y1="592" y2="880" x1="1632" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1632" y1="944" y2="944" x1="1504" />
            <wire x2="1504" y1="944" y2="976" x1="1504" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1840" y1="1440" y2="1440" x1="1184" />
            <wire x2="1920" y1="976" y2="976" x1="1840" />
            <wire x2="1840" y1="976" y2="1440" x1="1840" />
        </branch>
        <instance x="272" y="592" name="XLXI_5" orien="R0" />
        <instance x="272" y="832" name="XLXI_6" orien="R0" />
        <instance x="272" y="1040" name="XLXI_7" orien="R0" />
        <instance x="272" y="1312" name="XLXI_8" orien="R0" />
        <branch name="A">
            <wire x2="272" y1="560" y2="560" x1="112" />
        </branch>
        <branch name="B">
            <wire x2="224" y1="800" y2="800" x1="112" />
            <wire x2="272" y1="800" y2="800" x1="224" />
            <wire x2="224" y1="800" y2="896" x1="224" />
            <wire x2="576" y1="896" y2="896" x1="224" />
            <wire x2="576" y1="896" y2="976" x1="576" />
            <wire x2="960" y1="976" y2="976" x1="576" />
        </branch>
        <branch name="C">
            <wire x2="272" y1="1008" y2="1008" x1="112" />
        </branch>
        <branch name="D">
            <wire x2="192" y1="1280" y2="1280" x1="112" />
            <wire x2="272" y1="1280" y2="1280" x1="192" />
            <wire x2="192" y1="1152" y2="1280" x1="192" />
            <wire x2="1184" y1="1152" y2="1152" x1="192" />
            <wire x2="1248" y1="1008" y2="1008" x1="1184" />
            <wire x2="1184" y1="1008" y2="1152" x1="1184" />
        </branch>
        <iomarker fontsize="28" x="112" y="560" name="A" orien="R180" />
        <iomarker fontsize="28" x="112" y="800" name="B" orien="R180" />
        <iomarker fontsize="28" x="112" y="1280" name="D" orien="R180" />
        <iomarker fontsize="28" x="2304" y="944" name="Z" orien="R0" />
        <branch name="XLXN_10">
            <wire x2="960" y1="560" y2="560" x1="496" />
        </branch>
        <branch name="XLXN_12">
            <wire x2="688" y1="800" y2="800" x1="496" />
            <wire x2="720" y1="800" y2="800" x1="688" />
            <wire x2="688" y1="800" y2="1344" x1="688" />
            <wire x2="928" y1="1344" y2="1344" x1="688" />
            <wire x2="720" y1="624" y2="800" x1="720" />
            <wire x2="960" y1="624" y2="624" x1="720" />
        </branch>
        <branch name="XLXN_14">
            <wire x2="592" y1="1008" y2="1008" x1="496" />
            <wire x2="720" y1="1008" y2="1008" x1="592" />
            <wire x2="592" y1="1008" y2="1408" x1="592" />
            <wire x2="928" y1="1408" y2="1408" x1="592" />
            <wire x2="720" y1="912" y2="1008" x1="720" />
            <wire x2="960" y1="912" y2="912" x1="720" />
        </branch>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="1044" y="508">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="1044" y="480">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="340" y="464">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="340" y="492">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="340" y="720">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="340" y="748">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="340" y="928">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="340" y="956">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="340" y="1200">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="340" y="1228">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,255,0)" x="44" y="1232">Switch 4</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,255,0)" x="44" y="512">Switch 1</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,255,0)" x="40" y="752">Switch 2</text>
        <iomarker fontsize="28" x="112" y="1008" name="C" orien="R180" />
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,255,0)" x="48" y="972">Switch 3</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,255,0)" x="2304" y="896">LED 1</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="336" y="1076">74HC04</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="336" y="868">74HC04</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="336" y="1348">74HC04</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="336" y="628">74HC04</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="1044" y="596">74HC08</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="300" y="536">1</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="444" y="536">2</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="300" y="776">3</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="444" y="776">4</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="300" y="984">5</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="444" y="984">6</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="300" y="1256">13</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="444" y="1256">12</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="988" y="536">1</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="988" y="600">2</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1180" y="568">3</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="972" y="888">4</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="972" y="952">5</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="972" y="1016">1</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="956" y="1320">1</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="956" y="1384">2</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1644" y="856">1</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1644" y="920">2</text>
        <instance x="960" y="1040" name="XLXI_9" orien="R0" />
        <branch name="XLXN_16">
            <wire x2="1248" y1="944" y2="944" x1="1216" />
        </branch>
        <instance x="1248" y="1072" name="XLXI_10" orien="R0" />
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="1332" y="880">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="1332" y="908">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="1044" y="856">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="1044" y="884">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="1044" y="944">74HC08</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="1332" y="976">74HC08</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1172" y="920">6</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1284" y="920">13</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1284" y="984">12</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1460" y="952">11</text>
        <instance x="928" y="1600" name="XLXI_11" orien="R0" />
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="956" y="1448">4</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="956" y="1512">5</text>
        <branch name="XLXN_18">
            <wire x2="704" y1="1280" y2="1280" x1="496" />
            <wire x2="704" y1="1280" y2="1472" x1="704" />
            <wire x2="880" y1="1472" y2="1472" x1="704" />
            <wire x2="928" y1="1472" y2="1472" x1="880" />
            <wire x2="880" y1="1472" y2="1536" x1="880" />
            <wire x2="928" y1="1536" y2="1536" x1="880" />
        </branch>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="1012" y="1348">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="1012" y="1376">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="1012" y="1440">74HC21</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1144" y="1420">6</text>
        <instance x="1632" y="1008" name="XLXI_12" orien="R0" />
        <branch name="XLXN_19">
            <wire x2="1920" y1="912" y2="912" x1="1888" />
        </branch>
        <instance x="1920" y="1040" name="XLXI_13" orien="R0" />
        <branch name="Z">
            <wire x2="2304" y1="944" y2="944" x1="2176" />
        </branch>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="1992" y="840">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="1992" y="868">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="1712" y="808">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="1712" y="836">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="1716" y="912">74HC32</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="2004" y="944">74HC32</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1844" y="888">3</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1940" y="888">4</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1940" y="952">5</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="2132" y="920">6</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="92" y="1540">14</text>
        <text style="fontsize:20;fontname:Arial" x="92" y="1564">7</text>
    </sheet>
</drawing>