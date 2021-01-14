<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="CLK" />
        <signal name="CLR" />
        <signal name="XLXN_36" />
        <signal name="XLXN_37" />
        <signal name="VI" />
        <signal name="XLXN_56" />
        <signal name="AI" />
        <signal name="S1" />
        <signal name="S0" />
        <signal name="XLXN_65" />
        <signal name="XLXN_70" />
        <signal name="VD" />
        <signal name="AD" />
        <signal name="RD" />
        <signal name="RI" />
        <port polarity="Input" name="CLK" />
        <port polarity="Input" name="CLR" />
        <port polarity="Output" name="VI" />
        <port polarity="Output" name="AI" />
        <port polarity="Input" name="S1" />
        <port polarity="Input" name="S0" />
        <port polarity="Output" name="VD" />
        <port polarity="Output" name="AD" />
        <port polarity="Output" name="RD" />
        <port polarity="Output" name="RI" />
        <blockdef name="rom32x1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="320" y1="-384" y2="-384" x1="384" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-384" y2="-384" x1="0" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <rect width="256" x="64" y="-448" height="384" />
        </blockdef>
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
            <blockpin signalname="XLXN_36" name="D" />
            <blockpin signalname="XLXN_65" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_3">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="XLXN_56" name="D" />
            <blockpin signalname="XLXN_70" name="Q" />
        </block>
        <block symbolname="fdc" name="XLXI_4">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="CLR" name="CLR" />
            <blockpin signalname="XLXN_37" name="D" />
            <blockpin signalname="RD" name="Q" />
        </block>
        <block symbolname="rom32x1" name="XLXI_1">
            <attr value="0F090F0A" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="S1" name="A0" />
            <blockpin signalname="S0" name="A1" />
            <blockpin signalname="XLXN_65" name="A2" />
            <blockpin signalname="XLXN_70" name="A3" />
            <blockpin signalname="RD" name="A4" />
            <blockpin signalname="XLXN_36" name="O" />
        </block>
        <block symbolname="rom32x1" name="XLXI_5">
            <attr value="0FF00FF0" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="S1" name="A0" />
            <blockpin signalname="S0" name="A1" />
            <blockpin signalname="XLXN_65" name="A2" />
            <blockpin signalname="XLXN_70" name="A3" />
            <blockpin signalname="RD" name="A4" />
            <blockpin signalname="XLXN_56" name="O" />
        </block>
        <block symbolname="rom32x1" name="XLXI_6">
            <attr value="0FFFF000" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="S1" name="A0" />
            <blockpin signalname="S0" name="A1" />
            <blockpin signalname="XLXN_65" name="A2" />
            <blockpin signalname="XLXN_70" name="A3" />
            <blockpin signalname="RD" name="A4" />
            <blockpin signalname="XLXN_37" name="O" />
        </block>
        <block symbolname="rom32x1" name="XLXI_7">
            <attr value="0FFF0000" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="S1" name="A0" />
            <blockpin signalname="S0" name="A1" />
            <blockpin signalname="XLXN_65" name="A2" />
            <blockpin signalname="XLXN_70" name="A3" />
            <blockpin signalname="RD" name="A4" />
            <blockpin signalname="VI" name="O" />
        </block>
        <block symbolname="rom32x1" name="XLXI_12">
            <attr value="F0000000" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="S1" name="A0" />
            <blockpin signalname="S0" name="A1" />
            <blockpin signalname="XLXN_65" name="A2" />
            <blockpin signalname="XLXN_70" name="A3" />
            <blockpin signalname="RD" name="A4" />
            <blockpin signalname="AI" name="O" />
        </block>
        <block symbolname="rom32x1" name="XLXI_31">
            <attr value="00000FFF" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="S1" name="A0" />
            <blockpin signalname="S0" name="A1" />
            <blockpin signalname="XLXN_65" name="A2" />
            <blockpin signalname="XLXN_70" name="A3" />
            <blockpin signalname="RD" name="A4" />
            <blockpin signalname="VD" name="O" />
        </block>
        <block symbolname="rom32x1" name="XLXI_38">
            <attr value="0000F000" name="INIT">
                <trait verilog="all:0 dp:1nosynth wsynop:1 wsynth:1" />
                <trait vhdl="all:0 gm:1nosynth wa:1 wd:1" />
                <trait valuetype="BitVector 32 h" />
            </attr>
            <blockpin signalname="S1" name="A0" />
            <blockpin signalname="S0" name="A1" />
            <blockpin signalname="XLXN_65" name="A2" />
            <blockpin signalname="XLXN_70" name="A3" />
            <blockpin signalname="RD" name="A4" />
            <blockpin signalname="AD" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_39">
            <blockpin signalname="RD" name="I" />
            <blockpin signalname="RI" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1776" y="1248" name="XLXI_3" orien="R0" />
        <instance x="1776" y="1616" name="XLXI_4" orien="R0" />
        <instance x="2544" y="688" name="XLXI_1" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="0" y="-532" type="instance" />
        </instance>
        <instance x="2544" y="1072" name="XLXI_5" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="192" y="-298" type="instance" />
        </instance>
        <instance x="2544" y="1456" name="XLXI_6" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="192" y="-298" type="instance" />
        </instance>
        <instance x="2544" y="1840" name="XLXI_7" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="192" y="-298" type="instance" />
        </instance>
        <instance x="2544" y="2224" name="XLXI_12" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="192" y="-298" type="instance" />
        </instance>
        <instance x="1776" y="848" name="XLXI_2" orien="R0" />
        <branch name="CLK">
            <wire x2="1712" y1="1488" y2="1488" x1="1520" />
            <wire x2="1776" y1="1488" y2="1488" x1="1712" />
            <wire x2="1712" y1="720" y2="1120" x1="1712" />
            <wire x2="1744" y1="1120" y2="1120" x1="1712" />
            <wire x2="1776" y1="1120" y2="1120" x1="1744" />
            <wire x2="1712" y1="1120" y2="1488" x1="1712" />
            <wire x2="1776" y1="720" y2="720" x1="1712" />
        </branch>
        <instance x="2544" y="2608" name="XLXI_31" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="192" y="-298" type="instance" />
        </instance>
        <branch name="XLXN_36">
            <wire x2="1696" y1="176" y2="592" x1="1696" />
            <wire x2="1760" y1="592" y2="592" x1="1696" />
            <wire x2="1776" y1="592" y2="592" x1="1760" />
            <wire x2="2992" y1="176" y2="176" x1="1696" />
            <wire x2="2992" y1="176" y2="304" x1="2992" />
            <wire x2="2992" y1="304" y2="304" x1="2928" />
        </branch>
        <branch name="XLXN_37">
            <wire x2="1696" y1="1360" y2="2624" x1="1696" />
            <wire x2="3008" y1="2624" y2="2624" x1="1696" />
            <wire x2="1760" y1="1360" y2="1360" x1="1696" />
            <wire x2="1776" y1="1360" y2="1360" x1="1760" />
            <wire x2="3008" y1="1072" y2="1072" x1="2928" />
            <wire x2="3008" y1="1072" y2="2624" x1="3008" />
        </branch>
        <branch name="CLR">
            <wire x2="1728" y1="1584" y2="1584" x1="1520" />
            <wire x2="1776" y1="1584" y2="1584" x1="1728" />
            <wire x2="1728" y1="816" y2="1216" x1="1728" />
            <wire x2="1744" y1="1216" y2="1216" x1="1728" />
            <wire x2="1760" y1="1216" y2="1216" x1="1744" />
            <wire x2="1776" y1="1216" y2="1216" x1="1760" />
            <wire x2="1728" y1="1216" y2="1584" x1="1728" />
            <wire x2="1776" y1="816" y2="816" x1="1728" />
        </branch>
        <iomarker fontsize="28" x="1520" y="1488" name="CLK" orien="R180" />
        <iomarker fontsize="28" x="1520" y="1584" name="CLR" orien="R180" />
        <iomarker fontsize="28" x="1168" y="496" name="S0" orien="R180" />
        <iomarker fontsize="28" x="1168" y="560" name="S1" orien="R180" />
        <branch name="VI">
            <wire x2="2944" y1="1456" y2="1456" x1="2928" />
            <wire x2="2960" y1="1456" y2="1456" x1="2944" />
        </branch>
        <iomarker fontsize="28" x="2960" y="1456" name="VI" orien="R0" />
        <branch name="XLXN_56">
            <wire x2="1616" y1="224" y2="992" x1="1616" />
            <wire x2="1760" y1="992" y2="992" x1="1616" />
            <wire x2="1776" y1="992" y2="992" x1="1760" />
            <wire x2="2976" y1="224" y2="224" x1="1616" />
            <wire x2="2976" y1="224" y2="688" x1="2976" />
            <wire x2="2976" y1="688" y2="688" x1="2928" />
        </branch>
        <branch name="S1">
            <wire x2="1120" y1="2144" y2="2272" x1="1120" />
            <wire x2="1184" y1="2272" y2="2272" x1="1120" />
            <wire x2="1584" y1="2144" y2="2144" x1="1120" />
            <wire x2="1584" y1="2144" y2="2224" x1="1584" />
            <wire x2="2480" y1="2224" y2="2224" x1="1584" />
            <wire x2="2544" y1="2224" y2="2224" x1="2480" />
            <wire x2="1760" y1="560" y2="560" x1="1168" />
            <wire x2="1760" y1="304" y2="560" x1="1760" />
            <wire x2="2480" y1="304" y2="304" x1="1760" />
            <wire x2="2544" y1="304" y2="304" x1="2480" />
            <wire x2="2480" y1="304" y2="688" x1="2480" />
            <wire x2="2544" y1="688" y2="688" x1="2480" />
            <wire x2="2480" y1="688" y2="1072" x1="2480" />
            <wire x2="2544" y1="1072" y2="1072" x1="2480" />
            <wire x2="2480" y1="1072" y2="1456" x1="2480" />
            <wire x2="2544" y1="1456" y2="1456" x1="2480" />
            <wire x2="2480" y1="1456" y2="1840" x1="2480" />
            <wire x2="2544" y1="1840" y2="1840" x1="2480" />
            <wire x2="2480" y1="1840" y2="2224" x1="2480" />
        </branch>
        <branch name="S0">
            <wire x2="1184" y1="2336" y2="2336" x1="1120" />
            <wire x2="1120" y1="2336" y2="2656" x1="1120" />
            <wire x2="2432" y1="2656" y2="2656" x1="1120" />
            <wire x2="1856" y1="496" y2="496" x1="1168" />
            <wire x2="1856" y1="368" y2="496" x1="1856" />
            <wire x2="2432" y1="368" y2="368" x1="1856" />
            <wire x2="2544" y1="368" y2="368" x1="2432" />
            <wire x2="2432" y1="368" y2="752" x1="2432" />
            <wire x2="2544" y1="752" y2="752" x1="2432" />
            <wire x2="2432" y1="752" y2="1136" x1="2432" />
            <wire x2="2544" y1="1136" y2="1136" x1="2432" />
            <wire x2="2432" y1="1136" y2="1520" x1="2432" />
            <wire x2="2544" y1="1520" y2="1520" x1="2432" />
            <wire x2="2432" y1="1520" y2="1904" x1="2432" />
            <wire x2="2544" y1="1904" y2="1904" x1="2432" />
            <wire x2="2432" y1="1904" y2="2288" x1="2432" />
            <wire x2="2544" y1="2288" y2="2288" x1="2432" />
            <wire x2="2432" y1="2288" y2="2656" x1="2432" />
        </branch>
        <branch name="XLXN_65">
            <wire x2="1184" y1="2400" y2="2400" x1="1104" />
            <wire x2="1104" y1="2400" y2="2608" x1="1104" />
            <wire x2="2352" y1="2608" y2="2608" x1="1104" />
            <wire x2="2352" y1="592" y2="592" x1="2160" />
            <wire x2="2352" y1="592" y2="816" x1="2352" />
            <wire x2="2352" y1="816" y2="1200" x1="2352" />
            <wire x2="2544" y1="1200" y2="1200" x1="2352" />
            <wire x2="2352" y1="1200" y2="1584" x1="2352" />
            <wire x2="2544" y1="1584" y2="1584" x1="2352" />
            <wire x2="2352" y1="1584" y2="1968" x1="2352" />
            <wire x2="2544" y1="1968" y2="1968" x1="2352" />
            <wire x2="2352" y1="1968" y2="2352" x1="2352" />
            <wire x2="2544" y1="2352" y2="2352" x1="2352" />
            <wire x2="2352" y1="2352" y2="2608" x1="2352" />
            <wire x2="2544" y1="816" y2="816" x1="2352" />
            <wire x2="2352" y1="432" y2="592" x1="2352" />
            <wire x2="2544" y1="432" y2="432" x1="2352" />
        </branch>
        <branch name="XLXN_70">
            <wire x2="1184" y1="2464" y2="2464" x1="1136" />
            <wire x2="1136" y1="2464" y2="2688" x1="1136" />
            <wire x2="2336" y1="2688" y2="2688" x1="1136" />
            <wire x2="2336" y1="992" y2="992" x1="2160" />
            <wire x2="2336" y1="992" y2="1264" x1="2336" />
            <wire x2="2544" y1="1264" y2="1264" x1="2336" />
            <wire x2="2336" y1="1264" y2="1648" x1="2336" />
            <wire x2="2544" y1="1648" y2="1648" x1="2336" />
            <wire x2="2336" y1="1648" y2="2032" x1="2336" />
            <wire x2="2544" y1="2032" y2="2032" x1="2336" />
            <wire x2="2336" y1="2032" y2="2416" x1="2336" />
            <wire x2="2544" y1="2416" y2="2416" x1="2336" />
            <wire x2="2336" y1="2416" y2="2688" x1="2336" />
            <wire x2="2544" y1="496" y2="496" x1="2336" />
            <wire x2="2336" y1="496" y2="880" x1="2336" />
            <wire x2="2336" y1="880" y2="992" x1="2336" />
            <wire x2="2544" y1="880" y2="880" x1="2336" />
        </branch>
        <branch name="AI">
            <wire x2="2944" y1="1840" y2="1840" x1="2928" />
            <wire x2="2960" y1="1840" y2="1840" x1="2944" />
        </branch>
        <iomarker fontsize="28" x="2960" y="1840" name="AI" orien="R0" />
        <branch name="VD">
            <wire x2="2944" y1="2224" y2="2224" x1="2928" />
            <wire x2="2960" y1="2224" y2="2224" x1="2944" />
        </branch>
        <iomarker fontsize="28" x="2960" y="2224" name="VD" orien="R0" />
        <instance x="1184" y="2656" name="XLXI_38" orien="R0">
            <attrtext style="fontsize:28;fontname:Arial;displayformat:NAMEEQUALSVALUE" attrname="INIT" x="192" y="-298" type="instance" />
        </instance>
        <branch name="AD">
            <wire x2="1600" y1="2272" y2="2272" x1="1568" />
        </branch>
        <iomarker fontsize="28" x="1600" y="2272" name="AD" orien="R0" />
        <branch name="RD">
            <wire x2="880" y1="1072" y2="1264" x1="880" />
            <wire x2="928" y1="1264" y2="1264" x1="880" />
            <wire x2="2208" y1="1264" y2="1264" x1="928" />
            <wire x2="2208" y1="1264" y2="1360" x1="2208" />
            <wire x2="2320" y1="1360" y2="1360" x1="2208" />
            <wire x2="2320" y1="1360" y2="1712" x1="2320" />
            <wire x2="2544" y1="1712" y2="1712" x1="2320" />
            <wire x2="2320" y1="1712" y2="2096" x1="2320" />
            <wire x2="2544" y1="2096" y2="2096" x1="2320" />
            <wire x2="2320" y1="2096" y2="2480" x1="2320" />
            <wire x2="2544" y1="2480" y2="2480" x1="2320" />
            <wire x2="2320" y1="2480" y2="2672" x1="2320" />
            <wire x2="1184" y1="1072" y2="1072" x1="880" />
            <wire x2="928" y1="1168" y2="1264" x1="928" />
            <wire x2="1184" y1="2528" y2="2528" x1="1152" />
            <wire x2="1152" y1="2528" y2="2672" x1="1152" />
            <wire x2="2320" y1="2672" y2="2672" x1="1152" />
            <wire x2="2208" y1="1360" y2="1360" x1="2160" />
            <wire x2="2544" y1="560" y2="560" x1="2320" />
            <wire x2="2320" y1="560" y2="944" x1="2320" />
            <wire x2="2544" y1="944" y2="944" x1="2320" />
            <wire x2="2320" y1="944" y2="1328" x1="2320" />
            <wire x2="2320" y1="1328" y2="1360" x1="2320" />
            <wire x2="2544" y1="1328" y2="1328" x1="2320" />
        </branch>
        <instance x="928" y="1200" name="XLXI_39" orien="R0" />
        <branch name="RI">
            <wire x2="1184" y1="1168" y2="1168" x1="1152" />
        </branch>
        <iomarker fontsize="28" x="1184" y="1168" name="RI" orien="R0" />
        <iomarker fontsize="28" x="1184" y="1072" name="RD" orien="R0" />
    </sheet>
</drawing>