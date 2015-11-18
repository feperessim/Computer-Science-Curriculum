<?php
    // configuration
require("../includes/config.php");
// if form was submitted
if ($_SERVER["REQUEST_METHOD"] == "POST")
{
                $rows = query("SELECT * FROM users WHERE username = ?", $_POST["username"]);
            $row = $rows[0];
                
                
        
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide a username.");
        }
        
                if (empty($_POST["username"]))
        {
            apologize("You must provide a username.");
        }
        
        if (crypt($_POST["oldpassword"], $row["hash"]) != $row["hash"])
        {
            apologize("Sorry, the old Password was not correct.");
        }
        
                if ($_POST["password"] != $_POST["confirmation"])
                                {
                                        apologize("Missmatch. The new password does not match its Confirmation.");
        }
                
        else
        {
                        if(query("UPDATE users SET hash = ( ? ) WHERE username = ( ? )", crypt($_POST["password"]),$_POST["username"]) === false)
                                apologize("Sorry, some internal error occurred.");
                        else
                                redirect("index.php");
            
        }
        
        
}  
else
{
    // else render form
    render("change_password_form.php", ["title" => "Change Password"]);
}
?>
