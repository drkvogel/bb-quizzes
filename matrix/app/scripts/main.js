console.log('Starting Matrix Puzzle, ahem');

$("#content-container").on('click', 'a', function(e) {
	$(this).parent().html('<a href="#">A New link</a>');
	e.preventDefault();
});