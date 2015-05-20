<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>friend_list</title>
<script src="http://ajax.aspnetcdn.com/ajax/jQuery/jquery-1.8.0.js">
</script>
<script type="text/javascript">
function Returnto()
{
	var username = document.getElementById("username").innerHTML;
	var password = document.getElementById("password").innerHTML;
	window.location.href = "login?username="+username+"&password="+password;
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
		tr,td { text-align:center;font-family:"Comic Sans MS", cursive, sans-serif;}
	</style>
	<body>
		<h1><s:property value = "list_name"/></h1>
		<p id=username><s:property value = "username"/></p>
		<p id=password><s:property value = "password"/></p>	
		<p>列表</p>
		<center>
		<table border="1">
			<s:iterator value="friendlist" id="String" status = "status">
			<tr>
			<td>
				<p><s:property value="String"/></p>
			</td>
			</tr>
			</s:iterator>
		</table>
		<button onclick="Returnto()">ReturnBack</button>
		</center>
	</body>
</html>