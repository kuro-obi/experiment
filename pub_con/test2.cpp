#include <memory>
#include <atomic>
#include <thread>
#include <iostream>
#include <ranges>

static constexpr size_t num_tries = 50000;

struct Record
{
    bool done_;
    std::int64_t ts_;
    double bid_price_;
    double bid_qty_;
    double ask_price_;
    double ask_qty_;
};

typedef std::shared_ptr<Record> record_ptr_ty;

//auto load_order  = std::memory_order_relaxed;
//auto store_order = std::memory_order_relaxed;

//auto load_order  = std::memory_order_seq_cst;
//auto store_order = std::memory_order_seq_cst;

auto load_order  = std::memory_order_acquire;
auto store_order = std::memory_order_release;

record_ptr_ty rec_ = std::make_shared<Record>(Record{false, 0, 100., 1, 200, 1});

void write_1()
{
    for( int i = 0; i < num_tries; ++i)
    {
        auto rec = std::atomic_load_explicit(&rec_, load_order);
        rec->ts_ = i;
        rec->bid_price_ ++;
        rec->bid_qty_ ++;
        rec->ask_price_ ++;
        rec->ask_qty_ ++;
        std::atomic_store_explicit(&rec_,rec, store_order);
    }

    auto rec = std::atomic_load_explicit(&rec_, load_order);
    rec->done_ =  true;
    std::atomic_store_explicit(&rec_,rec, store_order);
}

void read_1()
{

    std::array<double,num_tries> bid_qty;
    bid_qty.fill(0);


    while( true )
    {
        auto rec = std::atomic_load_explicit(&rec_, load_order);
        bid_qty[rec->ts_] = rec->bid_qty_; 
        if(rec->done_)
        {
            break;
        }
    }

    std::cout<<"REC is:"<< rec_->done_ << " ts:"<< rec_->ts_ 
                << " bid:"<< rec_->bid_price_ << " " << rec_->bid_qty_ 
                << " ask:"<< rec_->ask_price_ << " " << rec_->ask_qty_ 
                << std::endl;

    //for(double  n : std::views::all(bid_qty) ) 
    //{
    //    std::cout << n << ' ';
    //}
    
}

void test_1()
{

    std::thread reader( [](){ read_1();});
    std::thread writer( [](){ write_1();});

    reader.join();
    writer.join();
}

int main(  )
{
    
    test_1();

}
