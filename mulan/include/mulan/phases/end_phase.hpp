#include <mulan/object.hpp>
#include <mulan/views/end_phase_view.hpp>
#include <mulan/phase_switcher.hpp>

#include <memory>

class end_phase : public object
{
public:
    end_phase(
        std::unique_ptr<end_phase_view> view,
        std::unique_ptr<end_phase_switcher> switcher
    );

    void draw() override;
    void update(float ms) override;

private:
    std::unique_ptr<end_phase_view> view_;
    std::unique_ptr<end_phase_switcher> switcher_;
};
