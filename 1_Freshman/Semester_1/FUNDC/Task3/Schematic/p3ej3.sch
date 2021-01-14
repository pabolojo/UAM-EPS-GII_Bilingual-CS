<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_98" />
        <signal name="XLXN_100" />
        <signal name="XLXN_125" />
        <signal name="XLXN_127" />
        <signal name="CLK" />
        <signal name="XLXN_131" />
        <signal name="XLXN_133" />
        <signal name="XLXN_135" />
        <signal name="XLXN_136" />
        <signal name="XLXN_137" />
        <signal name="XLXN_138" />
        <signal name="XLXN_139" />
        <signal name="XLXN_140" />
        <signal name="XLXN_141" />
        <signal name="XLXN_149" />
        <signal name="XLXN_150" />
        <signal name="XLXN_151" />
        <signal name="XLXN_153" />
        <signal name="XLXN_154" />
        <signal name="XLXN_155" />
        <signal name="XLXN_157" />
        <signal name="XLXN_164" />
        <signal name="XLXN_165" />
        <signal name="XLXN_166" />
        <signal name="INIT" />
        <signal name="SIG_DIV" />
        <signal name="XLXN_174" />
        <signal name="XLXN_175" />
        <signal name="XLXN_176" />
        <signal name="XLXN_193" />
        <signal name="XLXN_195" />
        <signal name="XLXN_196" />
        <signal name="XLXN_197" />
        <signal name="XLXN_199" />
        <signal name="XLXN_200" />
        <signal name="XLXN_201" />
        <signal name="XLXN_202" />
        <signal name="XLXN_203" />
        <signal name="XLXN_204" />
        <signal name="XLXN_205" />
        <port polarity="Input" name="CLK" />
        <port polarity="Input" name="INIT" />
        <port polarity="Output" name="SIG_DIV" />
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <blockdef name="cd4cle">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="64" y1="-384" y2="-384" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-576" y2="-576" x1="384" />
            <line x2="320" y1="-512" y2="-512" x1="384" />
            <line x2="320" y1="-448" y2="-448" x1="384" />
            <line x2="320" y1="-384" y2="-384" x1="384" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <rect width="256" x="64" y="-640" height="576" />
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
        <blockdef name="and8">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-512" x1="64" />
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <line x2="64" y1="-384" y2="-384" x1="0" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="144" y1="-336" y2="-336" x1="64" />
            <line x2="64" y1="-240" y2="-240" x1="144" />
            <arc ex="144" ey="-336" sx="144" sy="-240" r="48" cx="144" cy="-288" />
            <line x2="192" y1="-288" y2="-288" x1="256" />
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
        <block symbolname="cd4cle" name="XLXI_35">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_131" name="CE" />
            <blockpin signalname="XLXN_174" name="CLR" />
            <blockpin name="D0" />
            <blockpin name="D1" />
            <blockpin name="D2" />
            <blockpin name="D3" />
            <blockpin signalname="XLXN_133" name="L" />
            <blockpin signalname="XLXN_125" name="CEO" />
            <blockpin signalname="XLXN_203" name="Q0" />
            <blockpin signalname="XLXN_202" name="Q1" />
            <blockpin signalname="XLXN_201" name="Q2" />
            <blockpin signalname="XLXN_151" name="Q3" />
            <blockpin name="TC" />
        </block>
        <block symbolname="cd4cle" name="XLXI_36">
            <blockpin signalname="CLK" name="C" />
            <blockpin signalname="XLXN_125" name="CE" />
            <blockpin signalname="XLXN_174" name="CLR" />
            <blockpin name="D0" />
            <blockpin name="D1" />
            <blockpin name="D2" />
            <blockpin name="D3" />
            <blockpin signalname="XLXN_133" name="L" />
            <blockpin name="CEO" />
            <blockpin signalname="XLXN_199" name="Q0" />
            <blockpin signalname="XLXN_136" name="Q1" />
            <blockpin signalname="XLXN_137" name="Q2" />
            <blockpin signalname="XLXN_138" name="Q3" />
            <blockpin name="TC" />
        </block>
        <block symbolname="vcc" name="XLXI_39">
            <blockpin signalname="XLXN_131" name="P" />
        </block>
        <block symbolname="gnd" name="XLXI_40">
            <blockpin signalname="XLXN_133" name="G" />
        </block>
        <block symbolname="and8" name="XLXI_41">
            <blockpin signalname="XLXN_195" name="I0" />
            <blockpin signalname="XLXN_196" name="I1" />
            <blockpin signalname="XLXN_197" name="I2" />
            <blockpin signalname="XLXN_199" name="I3" />
            <blockpin signalname="XLXN_200" name="I4" />
            <blockpin signalname="XLXN_201" name="I5" />
            <blockpin signalname="XLXN_150" name="I6" />
            <blockpin signalname="XLXN_203" name="I7" />
            <blockpin signalname="SIG_DIV" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_42">
            <blockpin signalname="XLXN_136" name="I" />
            <blockpin signalname="XLXN_197" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_43">
            <blockpin signalname="XLXN_137" name="I" />
            <blockpin signalname="XLXN_196" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_44">
            <blockpin signalname="XLXN_138" name="I" />
            <blockpin signalname="XLXN_195" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_45">
            <blockpin signalname="XLXN_151" name="I" />
            <blockpin signalname="XLXN_200" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_46">
            <blockpin signalname="XLXN_202" name="I" />
            <blockpin signalname="XLXN_150" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_54">
            <blockpin signalname="XLXN_176" name="I0" />
            <blockpin signalname="INIT" name="I1" />
            <blockpin signalname="XLXN_174" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_57">
            <blockpin signalname="XLXN_205" name="I0" />
            <blockpin signalname="SIG_DIV" name="I1" />
            <blockpin signalname="XLXN_176" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_58">
            <blockpin signalname="CLK" name="I" />
            <blockpin signalname="XLXN_205" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="XLXN_125">
            <wire x2="1392" y1="1040" y2="1040" x1="1168" />
        </branch>
        <instance x="784" y="1232" name="XLXI_35" orien="R0" />
        <instance x="1392" y="1232" name="XLXI_36" orien="R0" />
        <instance x="544" y="1040" name="XLXI_39" orien="R0" />
        <branch name="XLXN_131">
            <wire x2="608" y1="1040" y2="1104" x1="608" />
            <wire x2="704" y1="1104" y2="1104" x1="608" />
            <wire x2="704" y1="1040" y2="1104" x1="704" />
            <wire x2="784" y1="1040" y2="1040" x1="704" />
        </branch>
        <branch name="CLK">
            <wire x2="736" y1="1248" y2="1248" x1="544" />
            <wire x2="1216" y1="1248" y2="1248" x1="736" />
            <wire x2="784" y1="1104" y2="1104" x1="736" />
            <wire x2="736" y1="1104" y2="1248" x1="736" />
            <wire x2="1216" y1="1104" y2="1104" x1="1184" />
            <wire x2="1216" y1="1104" y2="1248" x1="1216" />
            <wire x2="1392" y1="1104" y2="1104" x1="1216" />
            <wire x2="1184" y1="1104" y2="1360" x1="1184" />
            <wire x2="1856" y1="1360" y2="1360" x1="1184" />
            <wire x2="1856" y1="1168" y2="1360" x1="1856" />
            <wire x2="1984" y1="1168" y2="1168" x1="1856" />
            <wire x2="2048" y1="1168" y2="1168" x1="1984" />
        </branch>
        <instance x="448" y="1152" name="XLXI_40" orien="R0" />
        <branch name="XLXN_133">
            <wire x2="512" y1="960" y2="1024" x1="512" />
            <wire x2="720" y1="960" y2="960" x1="512" />
            <wire x2="720" y1="960" y2="976" x1="720" />
            <wire x2="784" y1="976" y2="976" x1="720" />
            <wire x2="720" y1="976" y2="1264" x1="720" />
            <wire x2="1232" y1="1264" y2="1264" x1="720" />
            <wire x2="1232" y1="976" y2="1264" x1="1232" />
            <wire x2="1392" y1="976" y2="976" x1="1232" />
        </branch>
        <iomarker fontsize="28" x="544" y="1248" name="CLK" orien="R180" />
        <branch name="XLXN_137">
            <wire x2="1888" y1="784" y2="784" x1="1776" />
        </branch>
        <branch name="XLXN_138">
            <wire x2="1888" y1="848" y2="848" x1="1776" />
        </branch>
        <instance x="1936" y="624" name="XLXI_45" orien="R0" />
        <branch name="XLXN_150">
            <wire x2="2304" y1="464" y2="464" x1="2160" />
        </branch>
        <instance x="1936" y="496" name="XLXI_46" orien="R0" />
        <branch name="XLXN_151">
            <wire x2="1232" y1="848" y2="848" x1="1168" />
            <wire x2="1232" y1="528" y2="848" x1="1232" />
            <wire x2="1840" y1="528" y2="528" x1="1232" />
            <wire x2="1840" y1="528" y2="592" x1="1840" />
            <wire x2="1936" y1="592" y2="592" x1="1840" />
        </branch>
        <instance x="576" y="1472" name="XLXI_54" orien="R0" />
        <branch name="INIT">
            <wire x2="576" y1="1344" y2="1344" x1="544" />
        </branch>
        <iomarker fontsize="28" x="544" y="1344" name="INIT" orien="R180" />
        <branch name="SIG_DIV">
            <wire x2="2304" y1="1104" y2="1104" x1="2256" />
            <wire x2="2256" y1="1104" y2="1264" x1="2256" />
            <wire x2="2624" y1="1264" y2="1264" x1="2256" />
            <wire x2="2576" y1="624" y2="624" x1="2560" />
            <wire x2="2624" y1="624" y2="624" x1="2576" />
            <wire x2="2736" y1="624" y2="624" x1="2624" />
            <wire x2="2624" y1="624" y2="1264" x1="2624" />
        </branch>
        <branch name="XLXN_174">
            <wire x2="784" y1="1200" y2="1280" x1="784" />
            <wire x2="896" y1="1280" y2="1280" x1="784" />
            <wire x2="896" y1="1280" y2="1376" x1="896" />
            <wire x2="1392" y1="1280" y2="1280" x1="896" />
            <wire x2="896" y1="1376" y2="1376" x1="832" />
            <wire x2="1392" y1="1200" y2="1280" x1="1392" />
        </branch>
        <instance x="2304" y="912" name="XLXI_41" orien="R0" />
        <instance x="1888" y="880" name="XLXI_44" orien="R0" />
        <instance x="1888" y="816" name="XLXI_43" orien="R0" />
        <instance x="1888" y="752" name="XLXI_42" orien="R0" />
        <branch name="XLXN_136">
            <wire x2="1888" y1="720" y2="720" x1="1776" />
        </branch>
        <branch name="XLXN_176">
            <wire x2="576" y1="1408" y2="1408" x1="560" />
            <wire x2="560" y1="1408" y2="1488" x1="560" />
            <wire x2="2640" y1="1488" y2="1488" x1="560" />
            <wire x2="2640" y1="1136" y2="1136" x1="2560" />
            <wire x2="2640" y1="1136" y2="1488" x1="2640" />
        </branch>
        <branch name="XLXN_195">
            <wire x2="2304" y1="848" y2="848" x1="2112" />
        </branch>
        <branch name="XLXN_196">
            <wire x2="2304" y1="784" y2="784" x1="2112" />
        </branch>
        <branch name="XLXN_197">
            <wire x2="2304" y1="720" y2="720" x1="2112" />
        </branch>
        <branch name="XLXN_199">
            <wire x2="2304" y1="656" y2="656" x1="1776" />
        </branch>
        <branch name="XLXN_200">
            <wire x2="2304" y1="592" y2="592" x1="2160" />
        </branch>
        <branch name="XLXN_201">
            <wire x2="1200" y1="784" y2="784" x1="1168" />
            <wire x2="1200" y1="784" y2="1216" x1="1200" />
            <wire x2="2240" y1="1216" y2="1216" x1="1200" />
            <wire x2="2240" y1="528" y2="1216" x1="2240" />
            <wire x2="2304" y1="528" y2="528" x1="2240" />
        </branch>
        <branch name="XLXN_202">
            <wire x2="1248" y1="720" y2="720" x1="1168" />
            <wire x2="1248" y1="464" y2="720" x1="1248" />
            <wire x2="1936" y1="464" y2="464" x1="1248" />
        </branch>
        <branch name="XLXN_203">
            <wire x2="1216" y1="656" y2="656" x1="1168" />
            <wire x2="1216" y1="400" y2="656" x1="1216" />
            <wire x2="2304" y1="400" y2="400" x1="1216" />
        </branch>
        <instance x="2304" y="1232" name="XLXI_57" orien="R0" />
        <iomarker fontsize="28" x="2736" y="624" name="SIG_DIV" orien="R0" />
        <branch name="XLXN_205">
            <wire x2="2304" y1="1168" y2="1168" x1="2272" />
        </branch>
        <instance x="2048" y="1200" name="XLXI_58" orien="R0" />
    </sheet>
</drawing>