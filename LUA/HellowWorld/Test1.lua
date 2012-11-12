io.write("Enter an ID number: ")
identification_number = tonumber(io.read())

if identification_number == nil then
	print("Invalid ID number.")
else
	if identification_number > 9000 and identification_number < 10000 then --If it's over 9000 and less than 10000
		print("Key, '" .. identification_number .. "', is valid.")
	else
		print("Access denied.")
	end
end
