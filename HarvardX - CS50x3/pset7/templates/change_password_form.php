<form action="change_password.php" method="post">
    <fieldset>
        <div class="control-group">
            
            <input name="username" value= 
            
            <?php 
            $user = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
                        echo ($user [0]['username']);
                        ?>
                   
                        type="text"/>
            
            <br /><br />
        </div>
        <div class="control-group">
                        <input autofocus name="oldpassword" placeholder="Old Password" type="password"/>
            <br/>
            <input name="password" placeholder="New Password" type="password"/>
            <br/>
            <input name="confirmation" placeholder="Confirmation" type="password"/>
            <br/>
        </div>
        <br/>
        <div class="control-group">
                        <button type="submit" class="btn">Chage Password!</button>
        </div>
    </fieldset>
</form>
<div>
</div>
