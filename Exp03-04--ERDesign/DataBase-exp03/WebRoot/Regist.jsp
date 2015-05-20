<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>RegistPage</title>
<script src="http://ajax.aspnetcdn.com/ajax/jQuery/jquery-1.8.0.js">
</script>
<script type="text/javascript">
function AlterUser(e)
{
	var username = document.getElementById("username").value;
	var sex = document.getElementById("sex").value;
	var birthday = document.getElementById("birthday").value;
	var address = document.getElementById("address").value;
	var password = document.getElementById("password").value;
	window.location.href = "AlterUser?username="+username+"&sex="+sex+"&birthday="+birthday+"&address="+address+"&password="+password;
}
function DeleteUser(e){
	var username = document.getElementById("username").value;
	var password = document.getElementById("password").value;
	window.location.href = "DeleteUser?username="+username+"&password="+password;
}
</script>
</head>
	<style>
		body{ background-color:#FFCC99; }
		h1,h2 { text-align:center;font-family:"Comic Sans MS", cursive, sans-serif;}	
		p {
			line-height:150%;
			text-align:center; font-family:"Comic Sans MS", cursive, sans-serif;
		}
	</style>
	
	<body>
		<h1>添加用户信息</h1>
		<center>
			<s:form action="Regist">
				<p>username:<input type="text" id="username" name="username"/></p>
				<p>sex:<input type="text" id="sex" name="sex"/></p>
				<p>birthday:<input type="text" id="birthday" name="birthday"/></p>
				<p>address:<input type="text" name="address"  id="address"/></p>
				<p>password:<input type="text" name="password"  id="password"/><p>
				<input type="submit" value="Submit"/> 
    		</s:form>
    		<button onclick="AlterUser(this)">AlterUser</button>
    		<button onclick="DeleteUser(this)">DeleteUser</button>
		</center>
	</body>
</html>