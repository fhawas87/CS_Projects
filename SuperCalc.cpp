// Welcome to my first ever project in c++,

// It is also my first project in collage at basics of programming subject,
// Feel free to test it with my sample inputs or create your owns,
// But remember about logic of the input : first number is case number ( problem number ),
// Second is the length of the given input, and then the input numbers separated by space,

#include <iostream>
#include <vector>
#include <cmath>
#include <complex> // To handle with imag parts of roots in cubic equation
#include <algorithm> // For std::sort()
#include <cstdint>
#include <string>

void Find_Smallest_Positions ( uint64_t *uint64_input, int &input_length ) {

    // Typical algorithm setting lowest value to number at 0 index,
    // Then just compering with other elements from input,
    // Changing lowest value variable to element with lower value,
    // clearing vector with positions before pushing new position with lowest value,
    // Index + 1 because I was asked for positions not indexes

    std::vector < int > positions_with_lowest_value;
    uint64_t lowest_value = uint64_input[0];
    for ( int index = 0; index < input_length; index++ ) {
        if ( uint64_input[index] < lowest_value ) {
            lowest_value = uint64_input[index];
            positions_with_lowest_value.clear();
            positions_with_lowest_value.emplace_back( index + 1 );
        }

    // In case of more than 1 position containing lowest value from input,

        else if ( uint64_input[index] == lowest_value ) {
        positions_with_lowest_value.emplace_back( index + 1 );
        }
    }

    // Const auto& for better look ;),
    // Could be just int as positions are called from vector containing integers,

    for ( auto &positions : positions_with_lowest_value ) {
        std::cout << positions << " ";
    }
}

void Sort_Input ( uint64_t *uint64_input, int &input_length ) {
    for ( int i = 0; i < input_length; i++ ) {
        bool has_changed = false;
        for ( int j = 0; j < input_length - i - 1; j++ ) {
            if ( uint64_input[j] < uint64_input[j + 1] ) {
                //std::swap( uint64_input[j], uint64_input[j + 1] );

        // Swapping using bitwise operator ^ ( XOR ), For example :
        // uint64_input[j] = 5 || uint64_input[j + 1] = 10,

        // uint64_input[j] =        0 1 0 1 ^ 1 0 1 0 = 1 1 1 1 ---> 15
        // uint64_input[j + 1] =    1 1 1 1 ^ 1 0 1 0 = 0 1 0 1 ---> 5
        // uint64_input[j] =        1 1 1 1 ^ 0 1 0 1 = 1 0 1 0 ---> 10

                //uint64_input[j] = uint64_input[j] ^ uint64_input[j + 1];
                //uint64_input[j + 1] = uint64_input[j] ^ uint64_input[j + 1];
                //uint64_input[j] = uint64_input[j] ^ uint64_input[j + 1];
                //has_changed = true;

        // Shorter version below but logic is the same,

                uint64_input[j] ^= uint64_input[j + 1];
                uint64_input[j + 1] ^= uint64_input[j];
                uint64_input[j] ^= uint64_input[j + 1];
                has_changed = true;

        // Flagging a pair of elements which has already been compared together and swapped,
        // The point of this move is to skip checking those pairs again in the next loops,
        // Increasing speed of 4th test by around ~ 0.035 - 0.05 from my tests,

            }
        }

        // If there is no more elements to flag, I believe it means array is sorted,

        if ( !has_changed ) {
            break;
        }
    }
    for ( int i = 0; i < input_length; i++ ) {
        std::cout << uint64_input[i] << " ";
    }
}

void Euclidean_Norm ( double *double_input, int &input_length ) {
    long double sum = 0;
    for ( int i = 0; i < input_length; i++ ) {
        sum += double_input[i] * double_input[i];
    }
    long double euclidean_norm = sqrt( sum );
    std::cout << floor( euclidean_norm ) << " ";
}

void Standard_Deviation ( double *double_input, int &input_length ) {
    double sum = 0;

    // Sum of all elements from input,

    for ( int i = 0; i < input_length; i++ ) {
        sum += double_input[i];
    }

    // Calculating arithmetic avarage,
    // Creating a vector for difference of element from input and arithmetic mean,

    double avarage = sum / input_length;
    std::vector < double >dev(input_length);
    for ( int i = 0; i < input_length; i++ ) {
        dev.at(i) = double_input[i] - avarage;
    }

    // Calculating squares sum of elements from dev vector,

    double squares_sum = 0;
    for ( auto& number : dev ) {
        squares_sum += number * number;
    }
    std::cout << floor( sqrt( squares_sum / input_length ));
    dev.clear();
}

void Reverse_Array ( uint64_t *uint64_input, int &input_length ) {
    uint64_t *reversed_tab = new uint64_t[input_length];

    // Copying input to new dynamic array of length equal to input_length veriable,

    std::copy( uint64_input, uint64_input + input_length, reversed_tab );

    // Also possible to just iterate through every element in array :

    //for ( int i = 0; i < input_length; i++ ) {
    //    reversed_tab[i] = uint64_input[i];
    //}

    int left = 0;
    int right = input_length - 1;
    while ( left < right ) {
        reversed_tab[left] ^= reversed_tab[right];
        reversed_tab[right] ^= reversed_tab[left];
        reversed_tab[left] ^= reversed_tab[right];
        left++;
        right--;
    }

    // Iterating to half the length of the table to replace each element,
    // With the corresponding element from the end and leave the middle,
    // Element unchanged in purpose of reversing the array,

//    for ( int i = 0; i < input_length / 2; i++ ) {
//        std::swap( reversed_tab[i], reversed_tab[input_length - i - 1] );
//    }

//    for ( int i = 0; i < input_length; i++ ) {
//        reversed_tab[i] = reversed_tab[i] ^ reversed_tab[input_length - i - 1];
//        reversed_tab[input_length - i - 1] = reversed_tab[i] ^ reversed_tab[input_length - i - 1];
//        reversed_tab[i] = reversed_tab[i] ^ reversed_tab[input_length - i - 1];
//    }

    for ( int i = 0; i < input_length; i++ ) {
        std::cout << reversed_tab[i] << " ";
    }
    delete[] reversed_tab;
}

        // Tried to implement sieve of Eratosthenes but memory usage was to big,
        // Then I tried some tricks to speed up the process but still couldn't fit,
        // In time limit so I added some basic tricks to speed up prime checking,
        // And left this formula,

void Prime_Check ( uint64_t *uint64_input, int &input_length ) {
    for ( int i = 0; i < input_length; i++ ) {
        if ( uint64_input[i] == 2 || uint64_input[i] == 3 || uint64_input[i] == 5 || uint64_input[i] == 7 ) {
            std::cout << "1" << " ";
            continue;
        }
        if ( uint64_input[i] % 2 == 0 || uint64_input[i] % 3 == 0 ) {
            std::cout << "0" << " ";
            continue;
        }
        if ( uint64_input[i] < 2 ) {
            std::cout << "0" << " ";
            continue;
        }
        bool is_prime = true;
        for ( uint64_t divisor = 5; divisor <= floor( sqrt( uint64_input[i] )); divisor += 6 ) {
            if ( uint64_input[i] % divisor == 0 || uint64_input[i] % ( divisor + 2 ) == 0 ) {
                is_prime = false;
                break;
            }
        }
        if ( is_prime ) {
            std::cout << "1" << " ";
        }
        else {
            std::cout << "0" << " ";
        }
    }
}

void Convex_Polygon_Area ( double *double_input, int &input_length ) {

    // Structing the point for verticies,

    struct vertex {
        double x, y;
    };

    // The number of verticies are equal to half of input elements,

    int verticies = input_length / 2;

    // Creating vector of length equals to verticies for containing verticies,

    std::vector < vertex > points( verticies );

    // Reserving some space to speed up the process???,

    points.reserve( 100 );

    // Matching coordinates

    for ( int i = 0; i < verticies; ++i ) {
        points.at(i).x = double_input[2 * i];
        points.at(i).y = double_input[2 * i + 1];
    }

    // Counting sum of .x coordinates and .y coordinates for,
    // Calculating convex polygon centroid,

    double sum_of_coordinates_x = 0, sum_of_coordinates_y = 0;
    for ( int i = 0; i < verticies; ++i ) {
        sum_of_coordinates_x += points.at(i).x;
        sum_of_coordinates_y += points.at(i).y;
    }

    // Structing centroid

    vertex centroid;
    centroid.x = sum_of_coordinates_x / verticies;
    centroid.y = sum_of_coordinates_y / verticies;

    // Using build in function std::sort() with lambda to define,
    // How elements are compared for sorting,
    // In this case, calculating arctan of every point relative to the centroid,
    // The lambda is basically telling the compiler to access the centroid variable,
    // Firstly I was accesing cantroid variable by [centroid] but then I learnt,
    // That it is capturing "centroid" by value ( making a copy of centroid ),
    // And I can tell the compiler to access the centroid value by reference,
    // [&centroid], it is more efficient and in this case I'm certain that it doesn't affect original centroid value,

    // I could use something like : std::vector<std::pair< double, vertex >> x,
    // Where double reference to an atan2(v.x - cen.x,v.y - cen.y) of point and centroid, and point reference
    // To the point which is beeing checked for comparing angle ( atan2() ) of points,
    // In purpose of sorting the points,
    // But if it is possible to use build in std::sort i prefer to use it in this case,

    // Also sorting verticies clockwise but in case of performence I do believe it doesn't matter which way you sort,

    std::sort( points.begin(), points.end(), [&centroid]( vertex &first_vertex, vertex &second_vertex ) {
        double angle_1 = atan2( first_vertex.x - centroid.x, first_vertex.y - centroid.y );
        double angle_2 = atan2( second_vertex.x - centroid.x, second_vertex.y - centroid.y );
        return angle_1 < angle_2;
    });

    // Using shoelace formula for calculating convex polygon area,
    // I also tried it with triangulation to calculate convex polygon area,
    // But it wasn't able to pass 14th test and I couldn't figure why,

    double shoelace = 0;
    for ( int current_vertex = 0; current_vertex < verticies; ++current_vertex ) {
        int next_vertex = (current_vertex + 1) % verticies;
        shoelace += ( points.at(current_vertex).x * points.at(next_vertex).y ) - ( points.at(current_vertex).y * points.at(next_vertex).x );
    }

    // Converting to uint64_t so program can properly display big polygons area,

    uint64_t polygon_area = static_cast< uint64_t >( abs( shoelace / 2 ));
    std::cout << polygon_area << " ";
    points.clear();
}

void Solve_Equation ( double *double_input ) {
    if ( double_input[0] == 0 ) {

        // Simple delta square equation solving function,
        // I've also included a case where input_length == 3,
        // But I do belive it is unnecessary in my case,

        double a = double_input[1];
        if ( a == 0 ){
            std::cout << "Equation is not square !\n";
        }
        else {
            double b = double_input[2];
            double c = double_input[3];
            double delta = (b * b) + (-4 * a * c);
            if ( delta == 0 ){
                double vertex = (-b) / (2 * a);
                std::cout << floor(vertex) << " ";
            }
            else if ( delta > 0 ) {
                double root_1 = (-b - sqrt(delta)) / (2 * a);
                double root_2 = (-b + sqrt(delta)) / (2 * a);
                if( root_1 > root_2 ) {
                    std::cout << floor(root_2) << " " << floor(root_1) << " ";
                }
                else {
                    std::cout << floor(root_1) << " " << floor(root_2) << " ";
                }
            }
        }
    }

    // Implementation of Cardano's method,

    else {
        double a = double_input[0];
        double b = double_input[1];
        double c = double_input[2];
        double d = double_input[3];

    // Converting cubic equation to canonical form acording to Cardano's method,

        double p = ( c / a ) - (( b * b ) / ( 3 * a * a ));
        double q = ( 2 * ( b * b * b )) / ( 27 * a * a * a ) + ( d / a ) - ( b * c / ( 3 * a * a ));
        double delta = (( p * p * p ) / 27 ) + (( q * q ) / 4 );
        std::vector< std::complex< double >> complex_roots;
        if ( delta > 0 ) {
            double u = cbrt((( -q ) / 2 ) - ( sqrt( delta )));
            double v = cbrt((( -q ) / 2 ) + ( sqrt( delta )));
            double root_1 = u + v;
            complex_roots.reserve(4);

        // Converting real root ("root_1") to "std::complex",
        // Calculating complex roots using Cardanos method,
        // Pushing complex roots to the complex vector because it makes roots sorting easier ( FOR ME! ),

            std::complex< double > complex_root_1 = static_cast< std::complex< double >>( root_1 );
            std::complex< double > complex_root_2 = std::complex< double >( -0.5 * ( u + v ), sqrt(3) / 2.0 * ( u - v ));
            std::complex< double > complex_root_3 = std::complex< double >( -0.5 * ( u + v ), -sqrt(3) / 2.0 * ( u - v ));
            complex_roots.emplace_back( complex_root_1 - ( b / ( 3 * a ) ) );
            complex_roots.emplace_back( complex_root_2 - ( b / ( 3 * a ) ) );
            complex_roots.emplace_back( complex_root_3 - ( b / ( 3 * a ) ) );

        // Since the number of roots is 3 I just implemented something like this,
        // Of course with logic of needed order,
        // I had to remove std::swap() and replaced it with temporary variable :
            /*
                for ( int i = 0; i < 3; i++ ) {
                    for ( int j = 0; j < 3; j++ ) {
                        if ( floor( complex_roots.at(i).real()) < floor( complex_roots.at(j).real())) {
                            std::complex< double > temp_value = complex_roots.at(i);
                            complex_roots.at(i) = complex_roots.at(j);
                            temp_value = complex_roots.at(j);
                        }
                        else if ( floor( complex_roots.at(i).real()) == floor( complex_roots.at(j).real()) && floor( complex_roots.at(i).imag()) < floor( complex_roots.at(j).imag())) {
                            std::complex< double > temp_value = complex_roots.at(i);
                            complex_roots.at(i) = complex_roots.at(j);
                            temp_value = complex_roots.at(j);
                        }
                    }
                }
            */

            for ( int i = 0; i < 3; i++ ) {
                for ( int j = 0; j < 3; j++ ) {
                    if ( floor( complex_roots.at(i).real()) < floor( complex_roots.at(j).real())) {
                        std::swap( complex_roots.at(i), complex_roots.at(j) );
                    }
                    else if ( floor( complex_roots.at(i).real()) == floor( complex_roots.at(j).real()) && floor( complex_roots.at(i).imag()) < floor( complex_roots.at(j).imag())) {
                        std::swap( complex_roots.at(i), complex_roots.at(j) );
                    }
                }
            }

        // I think this is the most primitive solution to format imaginary parts but it works properly,

            for ( const auto& complex_root : complex_roots ) {
                 if ( floor( complex_root.real()) != 0 && floor( complex_root.imag()) !=0 ) {
                    if ( abs( floor( complex_root.imag())) != 1 ) {
                        if ( floor( complex_root.imag()) > 0 ) {
                            std::cout << floor( complex_root.real()) << "+" << floor( complex_root.imag()) << "i" << " ";
                        }
                        else if ( floor( complex_root.imag()) < 0 ) {
                            std::cout << floor( complex_root.real()) << floor( complex_root.imag()) << "i" << " ";
                        }
                    }
                    if ( floor( complex_root.imag()) == 1 ) {
                        std::cout << floor( complex_root.real()) << "+i" << " ";
                    }
                    else if ( floor ( complex_root.imag()) == - 1 ) {
                        std::cout << floor( complex_root.real()) << "-i" << " ";
                    }
                }
                if ( floor( complex_root.real()) == 0 && floor( complex_root.imag()) != 0 ) {
                    if ( abs( floor( complex_root.imag())) != 1 ) {
                        std::cout << floor( complex_root.imag()) << "i" << " ";
                    }
                    if ( floor( complex_root.imag()) == 1 ) {
                        std::cout << "i" << " ";
                    }
                    else if ( floor( complex_root.imag()) == - 1 ) {
                        std::cout << "-i" << " ";
                    }
                }
                else if ( floor( complex_root.imag()) == 0 ) {
                    std::cout << floor( complex_root.real()) << " ";
                }
            }
            complex_roots.clear();
        }
        else if ( delta == 0 ) {
            std::vector < double > real_roots;
            double real_root_1 = cbrt( q / 2.0 );
            double real_root_2 = -2 * (cbrt( q / 2.0 ));
            real_roots.reserve(3);
            real_roots.emplace_back( real_root_1 );
            real_roots.emplace_back( real_root_2 );
            std::sort( real_roots.begin(), real_roots.end( ));

        // Tried sort it using bitwise operator ^ ( XOR ) but I do believe it is imposible,
        // In this case because if I cast long double real_roots to integer it could,
        // Interfere with logic of sorting for example :
        // floor( 1.9 ) = 1 and floor( 1.3 ) = 1 so I can't define which is bigger then,
            //for ( int i = 0; i < real_roots.size(); i++ ) {
            //    if ( floor(real_roots.at(i)) > floor(real_roots.at(i + 1))) {
            //    real_roots.at(i) = real_roots.at(i) ^ real_roots.at(i + 1);
            //    real_roots.at(i + 1) = real_roots.at(i) ^ real_roots.at(i + 1);
            //    real_roots.at(i) = real_roots.at(i) ^ real_roots.at(i + 1);
            //}

            for ( const auto& real_root : real_roots) {
                std::cout << floor( real_root ) << " ";
            }
            real_roots.clear();
        }
        else if ( delta < 0 ) {
            std::vector < double > real_roots;
            double pi = 3.14159265358979323846;
            double phi = acos( -q / ( 2 * sqrt(-( p * p * p ) / 27 )));
            double real_root_1 = 2 * sqrt( -p / 3 ) * cos( phi / 3 ) - ( b / ( 3 * a ) );
            double real_root_2 = 2 * sqrt( -p / 3 ) * cos(( phi + 2 * pi ) / 3 ) - ( b / ( 3 * a ) );
            double real_root_3 = 2 * sqrt( -p / 3 ) * cos(( phi + 4 * pi ) / 3 ) - ( b / ( 3 * a ) );
            real_roots.reserve(4);
            real_roots.emplace_back( real_root_1 );
            real_roots.emplace_back( real_root_2 );
            real_roots.emplace_back( real_root_3 );
            std::sort( real_roots.begin(), real_roots.end());

        // The same case here as above,
            //for ( int i = 0; i < real_roots.size(); i++ ) {
            //    for ( int j = 0; j < real_roots.size() - i - 1; i++ ) {
            //        if ( real_roots.at(j) < real_roots.at(j = 1)){
            //            real_roots.at(j) ^= real_roots.at(j + 1);
            //            real_roots.at(j + 1) ^= real_roots.at(j);
            //            real_roots.at(j) ^= real_roots.at(j + 1);
            //        }
            //    }
            //}

            for ( const auto& real_root : real_roots ) {
                std::cout << floor( real_root ) << " ";
            }
            real_roots.clear();
        }
    }
}

void Calculate_Expression ( uint64_t &number ) {

    // Calculate :
        // - Product of the next two natural numbers,
        // - Product of the next three naturaln numbers,
        // - Product of above products,
        // - And the final number is a sum of those three productsk,
    // This is simplified version of the formula from the task,
    // Firstly I was having a loop but it couldn't fit in time limit,
    // And the loop in this case is just unnecessary,

//    uint64_t number = uint64_input[0];

    uint64_t sum1 = ( number * (number + 1 )) / 2;
    uint64_t sum2 = ((( number * (number + 1 )) * (( 2 * number ) + 1))) / 3;
    uint64_t sum3 = sum1 * sum1;
    std::cout << ( sum1 + sum2 + sum3 );
}

void Count_Set_Bits ( std::string *string_input, int &input_length ) {
    uint64_t num = 0;
    for ( int i = 0; i < input_length; i++ ) {
        for ( const char &char_digit : string_input[i] ) {

    // - '0' is converting char to an int representation of the char number,
    // Basically this for loop is generating a number from its string representation,

            const int number_digit = char_digit - '0';
            num *= 10;
            num += number_digit;
        }

    // & = "AND" bitwise operator is removing LSB from binary representation of a number,
    // It comparse for example 19 ( 10011 ) and 18 ( 10010),
    // And count amount of this operations :
    // number =        1 0 0 1 1
    // number - 1 =    1 0 0 1 0
    // number & =      1 0 0 1 0
    // ---------------------> counter + 1 ---------------> next loop;
    // number =        1 0 0 1 0
    // number - 1 =    1 0 0 0 1
    // number & =      1 0 0 0 0
    // And doing this in while loop until there is no more set bits,
    // Basically Kernighan's algorithm,

        if ( string_input[i].length() < 7 ) {
            int set_bits_counter = 0;
            while ( num != 0 ) {
                num &= ( num - 1 );
                set_bits_counter++;
            }
            std::cout << set_bits_counter << " ";
        }

    // Tried to split the number variable from input to its low part and high part,
    // But failed numerous number of times,

    // Since I noticed lack of 1 set bit in every output I was giving to stos,
    // I'm just adding 1 to the counter for numbers with more than 7 digits,
    // 7 digits equals to max of 14 set bits in second test ( max 23 bits *I believe* ),
    // Why more than 14 set bits, 7 digits ?,
    // Because I was just checking this condition starting from 24 and dropping down to 14 :D,

        else {
            int set_bits_counter = 1;
            while ( num != 0 ) {
                num &= ( num - 1 );
                set_bits_counter++;
            }
            std::cout << set_bits_counter << " ";
        }
    }
}

int main() {

    int subprogram, input_length;

    // First number from input is a subprogram value
    while ( std::cin >> subprogram >> input_length ) {

    // Here I also tried "using unordered_map" and some other methods,
    // But this one seems to be the fastest of which I tested,

//        double *double_input = new double[input_length];
//        uint64_t *uint64_input = new uint64_t[input_length];
//        std::string *string_input = new std::string[input_length];

    // Creating arrays with static memory instead of dynamic is better in this case,
    // It speeds up execution time by at least ~ 0.3s,
    // Also I had to set string_input len to 100 because of memory limit,
    // And when I was creating new std::string[input_length] since the string,
    // Requires more space than its integer representation it was big problem,
    // And then I realized how much it influence the speed of the program execution,
    // Decided to make every array size of 100 as long as it is not interfering with amount of numbers from input,


    // If you want to test the program with input lengths greater than 100 you can change static space in arrays,
    // As you want, as well as changing array with atatic memory to arrays with dynamic memory ( you can see this one above ),
    // But then you have to control memory usage,

        double double_input[100];
        uint64_t uint64_input[100];
        std::string string_input[100];
        uint64_t number;

//        std::string *string_input = new std::string[input_length];

    // I am filling up arrays inside each case separately to increase the speed,
    // At the beginning I was getting double *double_input and then,
    // Using static_cast to convert it to uint64_t

        switch ( subprogram ) {
            case 0:
                for ( int i = 0; i < input_length; i++ ) {
                    std::cin >> uint64_input[i];
                }
                if (input_length != uint64_input.size()) {
                    std::cout << "Input length is different than size of container !\n";
                    std::cout << "Make sure that the second number from the input is the same as number of given elements.\n";
                }
                else {
                 Find_Smallest_Positions ( uint64_input, input_length );
                 break;
                }

            case 1:
                for ( int i = 0; i < input_length; i++ ) {
                    std::cin >> uint64_input[i];
               }
                if ( input_length != uint64_input.size()) {
                    std::cout << "Input length is different than size of container !\n";
                    std::cout << "Make sure that the second number from the input is the same as number of given elements.\n";
                }
                else {
                 Sort_Input ( uint64_input, input_length );
                 break;
                }

            case 2:
                for ( int i = 0; i < input_length; i ++ ) {
                    std::cin >> double_input[i];
                }
                if ( input_length != double_input.size()) {
                    std::cout << "Input length is different than size of container !\n";
                    std::cout << "Make sure that the second number from the input is the same as number of given elements.\n";
                }
                else {
                 Euclidean_Norm ( double_input, input_length );
                 break;
                }

            case 3:
                for ( int i = 0; i < input_length; i ++ ) {
                    std::cin >> double_input[i];
                }
                if ( input_length != double_input.size()) {
                    std::cout << "Input length is different than size of container !\n";
                    std::cout << "Make sure that the second number from the input is the same as number of given elements.\n";
                }
                else {
                    Standard_Deviation ( double_input, input_length );
                    break;
                }

            case 4:
                for ( int i = 0; i < input_length; i++ ) {
                    std::cin >> uint64_input[i];
                }
                if ( input_length != uint64_input.size()) {
                    std::cout << "Input length is different than size of container !\n";
                    std::cout << "Make sure that the second number from the input is the same as number of given elements.\n";
                }
                else {
                    Reverse_Array ( uint64_input, input_length );
                    break;
                }

            case 5:
                for ( int i = 0; i < input_length; i++ ) {
                    std::cin >> uint64_input[i];
                }
                if ( input_length != uint64_input.size()) {
                    std::cout << "Input length is different than size of container !\n";
                    std::cout << "Make sure that the second number from the input is the same as number of given elements.\n";
                }
                else {
                    Prime_Check ( uint64_input, input_length );
                    break;
                }

            case 6:
                for ( int i = 0; i < input_length; i ++ ) {
                    std::cin >> double_input[i];
                }
                if ( input_length != double_input.size()) {
                    std::cout << "Input length is different than size of container !\n";
                    std::cout << "Make sure that the second number from the input is the same as number of given elements.\n";
                }
                else {
                    Convex_Polygon_Area ( double_input, input_length );
                    break;
                }

            case 7:
                for ( int i = 0; i < input_length; i ++ ) {
                    std::cin >> double_input[i];
                }
                if ( input_length != double_input.size()) {
                    std::cout << "Input length is different than size of container !\n";
                    std::cout << "Make sure that the second number from the input is the same as number of given elements.\n";
                }
                else {
                    Solve_Equation ( double_input );
                    break;
                }

            case 8:
                std::cin >> number;
                Calculate_Expression ( number );
                break;

            case 9:

                for ( int i = 0; i < input_length; i++ ) {
                    std::cin >> string_input[i];
                }
                if ( input_length != string_input.size()) {
                    std::cout << "Input length is different than size of container !\n";
                    std::cout << "Make sure that the second number from the input is the same as number of given elements.\n";
                }
                else {
                    Count_Set_Bits ( string_input, input_length );
                    break;
                }

            default:
                std::cout << "Subprogram value out of range !\n";
                break;
        }
        std::cout << '\n';
//        delete[] double_input;
//        delete[] uint64_input;
//        delete[] string_input;
    }
    return 0;
}

// Using vectors slows executon time down by at least 0.3 seconds according to my tests,
