<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="A" />
        <signal name="B" />
        <signal name="C" />
        <signal name="XLXN_10" />
        <signal name="Z" />
        <signal name="D" />
        <signal name="XLXN_20" />
        <signal name="XLXN_21" />
        <signal name="XLXN_22" />
        <signal name="XLXN_25" />
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_30" />
        <signal name="XLXN_32" />
        <signal name="XLXN_33" />
        <signal name="XLXN_34" />
        <signal name="XLXN_38" />
        <signal name="XLXN_40" />
        <signal name="XLXN_46" />
        <signal name="XLXN_47" />
        <port polarity="Input" name="A" />
        <port polarity="Input" name="B" />
        <port polarity="Input" name="C" />
        <port polarity="Output" name="Z" />
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
        <block symbolname="inv" name="XLXI_2">
            <blockpin signalname="A" name="I" />
            <blockpin signalname="XLXN_10" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_3">
            <blockpin signalname="B" name="I" />
            <blockpin signalname="XLXN_20" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_4">
            <blockpin signalname="C" name="I" />
            <blockpin signalname="XLXN_26" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_5">
            <blockpin signalname="D" name="I" />
            <blockpin signalname="XLXN_30" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_13">
            <blockpin signalname="XLXN_27" name="I0" />
            <blockpin signalname="XLXN_28" name="I1" />
            <blockpin signalname="Z" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_14">
            <blockpin signalname="XLXN_20" name="I0" />
            <blockpin signalname="XLXN_10" name="I1" />
            <blockpin signalname="XLXN_28" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_15">
            <blockpin signalname="XLXN_30" name="I0" />
            <blockpin signalname="XLXN_20" name="I1" />
            <blockpin signalname="XLXN_25" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_17">
            <blockpin signalname="D" name="I0" />
            <blockpin signalname="B" name="I1" />
            <blockpin signalname="XLXN_22" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_18">
            <blockpin signalname="XLXN_22" name="I0" />
            <blockpin signalname="XLXN_25" name="I1" />
            <blockpin signalname="XLXN_21" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_19">
            <blockpin signalname="XLXN_21" name="I0" />
            <blockpin signalname="XLXN_26" name="I1" />
            <blockpin signalname="XLXN_27" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1120" y="1280" name="XLXI_2" orien="R0" />
        <instance x="1120" y="1520" name="XLXI_3" orien="R0" />
        <instance x="1120" y="1728" name="XLXI_4" orien="R0" />
        <instance x="1120" y="2000" name="XLXI_5" orien="R0" />
        <branch name="A">
            <wire x2="1120" y1="1248" y2="1248" x1="960" />
        </branch>
        <branch name="B">
            <wire x2="1072" y1="1488" y2="1488" x1="960" />
            <wire x2="1120" y1="1488" y2="1488" x1="1072" />
            <wire x2="1072" y1="1488" y2="1840" x1="1072" />
            <wire x2="1824" y1="1840" y2="1840" x1="1072" />
        </branch>
        <branch name="C">
            <wire x2="1120" y1="1696" y2="1696" x1="960" />
        </branch>
        <branch name="XLXN_10">
            <wire x2="1808" y1="1248" y2="1248" x1="1344" />
        </branch>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="1188" y="1152">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="1188" y="1180">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="1188" y="1408">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="1188" y="1436">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="1188" y="1616">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="1188" y="1644">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="1188" y="1888">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="1188" y="1916">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,255,0)" x="892" y="1920">Switch 4</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,255,0)" x="892" y="1200">Switch 1</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,255,0)" x="888" y="1440">Switch 2</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,255,0)" x="896" y="1660">Switch 3</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,255,0)" x="3152" y="1584">LED 1</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="1184" y="1764">74HC04</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="1184" y="1556">74HC04</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="1184" y="2036">74HC04</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="1184" y="1316">74HC04</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1148" y="1224">1</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1292" y="1224">2</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1148" y="1464">3</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1292" y="1464">4</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1148" y="1672">5</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1292" y="1672">6</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1148" y="1944">13</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1292" y="1944">12</text>
        <instance x="2768" y="1728" name="XLXI_13" orien="R0" />
        <branch name="Z">
            <wire x2="3152" y1="1632" y2="1632" x1="3024" />
        </branch>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="2840" y="1528">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="2840" y="1556">&gt;Gnd</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="2980" y="1608">6</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="940" y="2228">14</text>
        <text style="fontsize:20;fontname:Arial" x="940" y="2252">7</text>
        <iomarker fontsize="28" x="960" y="1248" name="A" orien="R180" />
        <iomarker fontsize="28" x="960" y="1488" name="B" orien="R180" />
        <iomarker fontsize="28" x="960" y="1968" name="D" orien="R180" />
        <iomarker fontsize="28" x="3152" y="1632" name="Z" orien="R0" />
        <iomarker fontsize="28" x="960" y="1696" name="C" orien="R180" />
        <branch name="D">
            <wire x2="1040" y1="1968" y2="1968" x1="960" />
            <wire x2="1120" y1="1968" y2="1968" x1="1040" />
            <wire x2="1824" y1="1904" y2="1904" x1="1040" />
            <wire x2="1040" y1="1904" y2="1968" x1="1040" />
        </branch>
        <instance x="1808" y="1376" name="XLXI_14" orien="R0" />
        <branch name="XLXN_20">
            <wire x2="1568" y1="1488" y2="1488" x1="1344" />
            <wire x2="1568" y1="1488" y2="1648" x1="1568" />
            <wire x2="1824" y1="1648" y2="1648" x1="1568" />
            <wire x2="1568" y1="1312" y2="1488" x1="1568" />
            <wire x2="1808" y1="1312" y2="1312" x1="1568" />
        </branch>
        <branch name="XLXN_27">
            <wire x2="2752" y1="1712" y2="1712" x1="2720" />
            <wire x2="2768" y1="1664" y2="1664" x1="2752" />
            <wire x2="2752" y1="1664" y2="1712" x1="2752" />
        </branch>
        <branch name="XLXN_28">
            <wire x2="2704" y1="1280" y2="1280" x1="2064" />
            <wire x2="2704" y1="1280" y2="1600" x1="2704" />
            <wire x2="2768" y1="1600" y2="1600" x1="2704" />
        </branch>
        <instance x="1824" y="1776" name="XLXI_15" orien="R0" />
        <branch name="XLXN_30">
            <wire x2="1360" y1="1968" y2="1968" x1="1344" />
            <wire x2="1824" y1="1712" y2="1712" x1="1360" />
            <wire x2="1360" y1="1712" y2="1968" x1="1360" />
        </branch>
        <instance x="2144" y="1840" name="XLXI_18" orien="R0" />
        <branch name="XLXN_25">
            <wire x2="2096" y1="1680" y2="1680" x1="2080" />
            <wire x2="2096" y1="1680" y2="1712" x1="2096" />
            <wire x2="2144" y1="1712" y2="1712" x1="2096" />
        </branch>
        <branch name="XLXN_22">
            <wire x2="2128" y1="1872" y2="1872" x1="2080" />
            <wire x2="2144" y1="1776" y2="1776" x1="2128" />
            <wire x2="2128" y1="1776" y2="1872" x1="2128" />
        </branch>
        <branch name="XLXN_26">
            <wire x2="1360" y1="1696" y2="1696" x1="1344" />
            <wire x2="1360" y1="1568" y2="1696" x1="1360" />
            <wire x2="2160" y1="1568" y2="1568" x1="1360" />
            <wire x2="2160" y1="1568" y2="1680" x1="2160" />
            <wire x2="2464" y1="1680" y2="1680" x1="2160" />
        </branch>
        <branch name="XLXN_21">
            <wire x2="2464" y1="1744" y2="1744" x1="2400" />
        </branch>
        <instance x="2464" y="1808" name="XLXI_19" orien="R0" />
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="2852" y="1632">74HC32</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="2772" y="1576">4</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="2772" y="1640">5</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="2356" y="1720">3</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="2148" y="1688">1</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="2148" y="1752">2</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="2228" y="1744">74HC32</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="2232" y="1640">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="2232" y="1668">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="2552" y="1608">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="2552" y="1636">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="1912" y="1576">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="1912" y="1604">&gt;Gnd</text>
        <instance x="1824" y="1968" name="XLXI_17" orien="R0" />
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="1912" y="1768">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="1912" y="1796">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(255,0,0)" x="1896" y="1176">&gt;Vcc</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,0)" x="1896" y="1204">&gt;Gnd</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="1908" y="1872">74HC08</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="1908" y="1680">74HC08</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="2548" y="1712">74HC08</text>
        <text style="fontsize:20;fontname:Arial;textcolor:rgb(0,0,255)" x="1892" y="1280">74HC08</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1836" y="1224">1</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1836" y="1288">2</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="2028" y="1256">3</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1852" y="1624">4</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1852" y="1688">5</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="2044" y="1656">6</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1852" y="1816">13</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="1852" y="1880">12</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="2044" y="1848">11</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="2492" y="1656">10</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="2492" y="1720">9</text>
        <text style="fontsize:24;fontname:Arial;textcolor:rgb(0,0,0)" x="2684" y="1688">8</text>
    </sheet>
</drawing>