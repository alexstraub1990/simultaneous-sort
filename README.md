# Simultaneous Sort
Small header-only library for providing the possibility to simultaneously sort multiple arrays, based on a comparator for the first one.

Being in the situation of having multiple arrays, you might want to sort one of them using a comparator, and have the others mimic its reordering. To prevent needless copying into one array composed of tuples, which hold the values from each input array, this small library implements a proxy object and uses value-wrapping. This way, only the value of the first array is exposed and no copying needs to be performed.
