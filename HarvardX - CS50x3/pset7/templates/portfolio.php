<div>
<?php require("../templates/nav_pills.php"); ?>

<table class="table table-striped" id="portfolio">

    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th style="text-align: right">Shares</th>
            <th style="text-align: right">Price</th>
            <th style="text-align: right">TOTAL</th>
        </tr>
    </thead>
    
    <tbody>
        <?php

            foreach ($positions as $position)
            {
                print("<tr>");
                print("<td>" . $position["symbol"] . "</td>");
                print("<td>" . $position["name"] . "</td>");
                print("<td>" . number_format($position["shares"]) . "</td>");
                print("<td> $" . number_format($position["price"],2) . "</td>");
                print("<td> $" . number_format($position["shares"]*$position["price"],2) . "</td>");
                print("</tr>");
            }

        ?>
        <tr>
            <td >CASH</td>
            <td >-</td>
            <td ><?=number_format($cash)?></td>
            <td >$1.00</td>
            <td>$<?=number_format($cash,2)?></td>
        </tr>

    </tbody>

</table>
