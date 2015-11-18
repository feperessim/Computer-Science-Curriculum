<?php

    // configuration
    require("../includes/config.php"); 

    $rows = query("SELECT * FROM holdings where id = ?", $_SESSION["id"]);

    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    $rows = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $cash = $rows[0]["cash"];

    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "id" => $_SESSION["id"], "cash" => $cash, "positions" => $positions]);
?>
