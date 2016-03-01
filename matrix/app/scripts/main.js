console.log('Starting Matrix Puzzle');

$("#content-container").on('click', 'a', function(e) {
	$(this).parent().html('<a href="#">New link</a>');
	e.preventDefault();
});