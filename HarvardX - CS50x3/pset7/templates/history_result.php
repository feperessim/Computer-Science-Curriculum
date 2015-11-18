<div>
<?php require("../templates/nav_pills.php"); ?>

<table class="table table-striped" id="history">

    <thead>
        <tr>
            <th>Date/Time</th>
            <th>Transaction</th>
            <th>Symbol</th>
            <th style="text-align: right">Shares</th>
            <th style="text-align: right">Price</th>
            <th style="text-align: right">Cash Flow</th>
        </tr>
    </thead>
    
    <tbody>

        <?php
           // dump($history);
            foreach ($history as $transaction)
            {
                print("<tr>");
                print("<td>" . $transaction["date"] . "</td>");
                print("<td>" . $transaction["type"] . "</td>");
                print("<td>" . $transaction["symbol"] . "</td>");
                print("<td>" . number_format($transaction["shares"]) . "</td>");
                print("<td> $" . number_format($transaction["price"],2) . "</td>");
                print("<td> $" . number_format($transaction["shares"]*$transaction["price"]*(($transaction["type"]=="Sell")?(-1):(1)),2) . "</td>");
                print("</tr>");
            }

        ?>
    </tbody>
</table>

