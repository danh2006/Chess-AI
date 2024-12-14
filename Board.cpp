    #include "Board.h"


    /**
        * @brief Computes the Zobrist hash of the given chess board.
        * @note This function should only be initialized once.
    */
    void Board::hash_board(){
        for(int pos = 0; pos < 64; ++pos) {
            if(board[pos] != Empty) {
                auto piece_index = get_piece_index(board[pos]);
                hash_value ^= piece_values[side][piece_index][pos];
            }
        }
        hash_value ^= side_to_move_values[side];
        // if(board.en_passant_square != Empty) {
        //     hash_value ^= en_passant_values[board.en_passant_square];
        // }
    }

    void Board::init() {
        static const int16_t default_value[64] = {
            -500, -320, -325, -950, -10000, -325, -320, -500,
            -100, -100, -100, -100, -100, -100, -100, -100,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            100, 100, 100, 100, 100, 100, 100, 100,
            500, 320, 325, 950, 10000, 325, 320, 500
        };
        memcpy(board, default_value, sizeof(board));
        white_can_kingside_castle  = true;
        white_can_queenside_castle = true;
        black_can_kingside_castle  = true;
        black_can_queenside_castle = true;
        side = White;
        Board::hash_board();
        cnt_move = 0;
        score = 0;
    }

    bool Board::is_empty(int16_t position) {
        return board[position] == Empty;
    }

    bool Board::is_white(int16_t position) {
        return board[position] > 0;
    }

    bool Board::is_black(int16_t position) {
        return board[position] < 0;
    }

    bool Board::get_side() {
        return side;
    }
    uint64_t Board::get_hash_key() {
        return hash_value;
    }
    int16_t Board::get_score() {
        return side == White ? score : -score;
    }

    Board Board::operator=(Board& rhs) {
        memcpy(rhs.board, board, sizeof(board));
        white_can_kingside_castle  = rhs.white_can_kingside_castle;
        white_can_queenside_castle = rhs.white_can_queenside_castle;
        black_can_kingside_castle  = rhs.black_can_kingside_castle;
        black_can_queenside_castle = rhs.black_can_queenside_castle;
        hash_value = rhs.hash_value;
        last_move  = rhs.last_move;
        score      = rhs.score;
        cnt_move   = rhs.cnt_move;
        side       = rhs.side;
        return *this;
    }

    int16_t& Board::operator[](int16_t idx) {
        return board[idx];
    }

    const int16_t& Board::operator[](int16_t idx) const {
        return board[idx];
    }

    bool Board::can_promotion(int16_t from, int16_t to) {
        const int16_t promotion_row = side == White ? 7 : 0;
        const int16_t cur_row = to >> 3;
        auto base = side == White ? 1 : -1;
        return board[from] == base * Pawn && cur_row == promotion_row;
    }

    bool Board::is_valid_move(int16_t position){
        if(side == White && is_black(position)) return false;
        if(side == Black && is_white(position)) return false;
        return true;
    }

    bool Board::can_kingside_castle() {
        auto kingside_castle = side == White ? white_can_kingside_castle : black_can_kingside_castle;
        auto king_position   = side == White ? 60 : 4;
        auto rook_position   = side == White ? 63 : 7;
        auto base = side == White ? 1 : -1;
        for (int i = king_position + 1; i < rook_position; i++) {
            if(board[i] != Empty) return false;
        }
        return kingside_castle && board[king_position] == base * King && board[rook_position] == base * Rook;
    }

    bool Board::can_queenside_castle() {
        auto queenside_castle = side == White ? white_can_queenside_castle : black_can_queenside_castle;
        auto king_position    = side == White ? 60 : 4;
        auto rook_position    = side == White ? 56 : 0;
        auto base = side == White ? 1 : -1;
        for (int i = rook_position + 1; i < king_position; i++) {
            if(board[i] != Empty) return false;
        }
        return queenside_castle && board[king_position] == base * King && board[rook_position] == base * Rook;
    }

    void Board::update_move_info() {
        hash_value ^= side_to_move_values[side];
        hash_value ^= side_to_move_values[!side];
        cnt_move += 1;
        side ^= 1;
    }

    void Board::kingside_castle(){
        auto king_position = side == White ? 60 : 4;
        auto rook_position = side == White ? 63 : 7;
        auto base = side == White ? 1 : -1;
        board[king_position + 2] = base * King;
        board[rook_position - 2] = base * Rook;
        board[king_position] = Empty;
        board[rook_position] = Empty;
        score += side == White ? 40 : -40;
        Board::update_move_info();
        hash_value ^= castling_values[side][Kingside];
    }

    void Board::queenside_castle(){
        auto king_position = side == White ? 60 : 4;
        auto rook_position = side == White ? 56 : 0;
        auto base = side == White ? 1 : -1;
        board[king_position - 2] = base * King;
        board[rook_position + 3] = base * Rook;
        board[king_position] = Empty;
        board[rook_position] = Empty;
        score += side == White ? 40 : -40;  
        Board::update_move_info();
        hash_value ^= castling_values[side][Queenside];
    }

    void Board::set_castled() {
        if(side == Black)
            white_can_kingside_castle = false,
            white_can_queenside_castle = false;
        else
            black_can_kingside_castle = false,
            black_can_queenside_castle = false;
    }

    template<class H>
    auto Board::get_piece_score(H&& evaluate_board, int16_t position) {
        if (is_black(position)) {
            position = Evaluate::flip[position];
        }
        return evaluate_board[position];
    }

    std::vector<int16_t> Board::get_all_move_pos(int16_t position) {
        const int16_t absolute_piece_value = abs(board[position]);
        switch (absolute_piece_value) {
            case Pawn:   return pawn_move(board, position);
            case Knight: return knight_move(board, position);
            case Bishop: return bishop_move(board, position);
            case Rook:   return rook_move(board, position);
            case Queen:  return queen_move(board, position);
            case King:   return king_move(board, position);
            default:
                mes_error("There are no pieces in this position.");
        }
        return std::vector<int16_t>{};
    }

    auto& Board::get_evaluate_board(int16_t position) {
        auto absolute_piece_value = abs(board[position]);
        switch (absolute_piece_value) {
            case Pawn:   return Evaluate::pawn;
            case Knight: return Evaluate::knight;
            case Bishop: return Evaluate::bishop;
            case Rook:   return Evaluate::rook;
            case Queen:  return Evaluate::queen;
            case King:   return Evaluate::king;
            default:
                return Evaluate::empty;
        }
    }

    int16_t Board::evaluate_score(int16_t from, int16_t to) {
        auto&& evaluate_board_from_pos = get_evaluate_board(from);
        auto&& evaluate_board_to_pos   = get_evaluate_board(to);
        int base = is_white(from) ? 1 : -1;
        int16_t evaluate = 0;
        evaluate += base * (get_piece_score(evaluate_board_from_pos, to) -
                            get_piece_score(evaluate_board_from_pos, from));
        
        hash_value ^= piece_values[side][get_piece_index(board[from])][from];
        hash_value ^= piece_values[side][get_piece_index(board[from])][to];

        if (board[to] != 0) {
            evaluate   -= board[to] + base * get_piece_score(evaluate_board_to_pos, to);
            hash_value ^= piece_values[!side][get_piece_index(board[to])][to];
        } 
        return evaluate;
    }

    int16_t Board::get_attack_value(int16_t from, int16_t to) {
        const auto captured_piece_value = board[to];
        const auto attack_piece_value   = board[from];

        return Attack::attacked[get_piece_index(captured_piece_value)][get_piece_index(attack_piece_value)];
    }

    void Board::change_castle_info(int16_t from) {
        auto& kingside_castle  = side == White ? white_can_kingside_castle  : black_can_kingside_castle;
        auto& queenside_castle = side == White ? white_can_queenside_castle : black_can_queenside_castle;
        auto king_position = side == White ? 60 : 4;
        auto kingside_rook_position  = side == White ? 63 : 7;
        auto queenside_rook_position = side == White ? 56 : 0;
        if(from == king_position || from == kingside_rook_position) {
            kingside_castle = false;
        }
        if(from == king_position || from == queenside_rook_position) {
            queenside_castle = false;
        }
    }

    /**
    * @brief Changes the position of a piece on the board.
    */
    void Board::change_piece_position(int16_t from, int16_t to) {   
        score += evaluate_score(from, to);

        // castle check king or rook move, if move, set castle info is false
        change_castle_info(from);
        
        if (can_promotion(from, to)) { 
            int16_t base = side == White ? 1 : -1;
            score += base * get_piece_score(Evaluate::queen, to);
            score += base * (Queen - Pawn);
            board[to] = base * Queen;
        }
        else {
            board[to] = board[from];
        }

        Board::update_move_info();
        last_move = MoveInfo(from, to);
        board[from] = 0;
    }

    void Board::simulation(std::vector<int16_t>& command) {
        for (int i = 0; i < command.size(); i += 2) {
            auto from = command[i];
            auto to   = command[i + 1];
            if(from == -1) {
                kingside_castle(); set_castled();
                continue;
            }
            if(from == -2) {
                queenside_castle(); set_castled();
                continue;
            }

            if (!is_valid_move(from)) mes_error("Invalid move");

            Board::change_piece_position(from, to);
        }
    }

    void Board::display() {
        for (int i = 0; i < 64; ++i) {
            if (i % 8 == 0)
                std::cout << 8 - i / 8 << ' ';

            std::cout << get_piece_unicode_symbol(board[i]);

            if ((i + 1) % 8 == 0)
                std::cout << "\n";
        }
        std::cout << ' ';
        for (int i = 0; i < 8; ++i)
            std::cout << " " << char('a' + i);
        std::cout << "\n";
    }
