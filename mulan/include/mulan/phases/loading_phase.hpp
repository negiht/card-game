#include <mulan/object.hpp>
#include <mulan/phase_switcher.hpp>
#include <mulan/views/loading_phase_view.hpp>

#include <memory>

class loading_phase : public object
{
public:
    loading_phase(
        std::unique_ptr<loading_phase_view> view,
        std::unique_ptr<loading_phase_switcher> switcher
    );

    void draw() override;
    void update(float ms) override;

private:
    std::unique_ptr<loading_phase_view> view_;
    std::unique_ptr<loading_phase_switcher> switcher_;
};
