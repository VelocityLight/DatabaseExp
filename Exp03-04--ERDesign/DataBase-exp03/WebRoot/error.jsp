<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>ErrorInf</title>
<script src="http://ajax.aspnetcdn.com/ajax/jQuery/jquery-1.8.0.js">
</script>
<script type="text/javascript">
function Returnto()
{
	window.location.href = "Regist.jsp";
}
</script>
</head>
	<style>
		h1,h2 { text-align:center;font-family:"Comic Sans MS", cursive, sans-serif;}	
		p {
			line-height:150%;
			text-align:center; font-family:"Comic Sans MS", cursive, sans-serif;
		}
		tr,td { text-align:center;font-family:"Comic Sans MS", cursive, sans-serif;}
	</style>
	<body>
		<h1>Sorry,User has already existed.Or Not Null</h1>
		<center><button onclick="Returnto()">ReturnBack</button></center>
	</body>
</html>